#include "car.h"
#define PI 3.14159265358979323846


//float lerp(float min, float max, float t) {
    //return min + (max - min) * t;
//}

float sign(float val) {
    if (!val) 
        return 0.0f;

    return val < 0.0f ? -1.0f : 1.0f;
}

float pacejka(float slipAngle) {
    float x = -slipAngle;
    float B = 1.714f;
    float C = 1.40f;
    float D = 1.00f;
    float E = -0.20f;

    return D * sin(C * atan(B * x - E * (B * x - atan(B * x))));
}


Car::Car(const CarData& carData) {
    this->data = carData;
    this->hullModel= std::make_unique<Model>("./res/models/car/hull.obj");

    glm::vec3 flWheelPos = glm::vec3(-2.05f, 0.5f, 1.1f);
    glm::vec3 frWheelPos = glm::vec3(-2.05f, 0.5f, -1.1f);
    glm::vec3 blWheelPos = glm::vec3(1.75f, 0.5f, 1.1f);
    glm::vec3 brWheelPos = glm::vec3(1.75f, 0.5f, -1.1f);

    this->wheel_fl = std::make_unique<Wheel>("./res/models/car/wheel_l.obj", flWheelPos);
    this->wheel_fr = std::make_unique<Wheel>("./res/models/car/wheel_r.obj", frWheelPos);
    this->wheel_bl = std::make_unique<Wheel>("./res/models/car/wheel_l.obj", blWheelPos);
    this->wheel_br = std::make_unique<Wheel>("./res/models/car/wheel_r.obj", brWheelPos);
}


void Car::draw(Shader& shader) {
    glm::mat4 carTransform(1.0f);
    carTransform = glm::translate(carTransform, pos);
    carTransform = glm::scale(carTransform, glm::vec3(0.7196245f));     // convert from model size to metres
    carTransform = glm::rotate(carTransform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));    // car model is flipped, so we flip it back to point in the +x axis
    carTransform = glm::rotate(carTransform, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    hullModel->draw(shader, carTransform);

    wheel_fr->draw(shader, carTransform);
    wheel_fl->draw(shader, carTransform);
    wheel_br->draw(shader, carTransform);
    wheel_bl->draw(shader, carTransform);
}


void Car::update(float dt) {
    wheel_fr->setSteeringAngle(steeringAngle);
    wheel_fl->setSteeringAngle(steeringAngle);

    // get velocity in local car coordinates from world coords
    float sn = sin(-yaw);
    float cs = cos(-yaw);
    velCar.x = cs * vel.x + sn * vel.z;
    velCar.z = cs * vel.z - sn * vel.x;

    // calculate weight on tires
    float weightTotal = data.mass * 9.81f;
    float wRear = data.weightRatio * weightTotal;
    float wFront = (1 - data.weightRatio) * weightTotal;
    weightRear = wRear + accelCar.x * (0.5 * data.height / data.wheelBase) * data.mass * 0.2f;
    weightFront = wFront - accelCar.x * (0.5 * data.height / data.wheelBase) * data.mass * 0.2f;

    wheel_bl->setWeight(weightRear / 2);
    wheel_br->setWeight(weightRear / 2);
    wheel_fl->setWeight(weightFront / 2);
    wheel_fr->setWeight(weightFront / 2);

    float wheelAngularVel = velCar.x / wheel_bl->getRadius();
    wheel_bl->setAngularVel(wheelAngularVel);
    wheel_fl->setAngularVel(wheelAngularVel);
    wheel_br->setAngularVel(wheelAngularVel);
    wheel_fr->setAngularVel(wheelAngularVel);

    // update wheels
    wheel_bl->update(dt);
    wheel_fl->update(dt);
    wheel_br->update(dt);
    wheel_fr->update(dt);

    // calculate engine rpm and clamp it to the redline
    engineRpm = (wheelAngularVel * data.gearRatios[selectedGear] * data.finalRatio * 60) / (2 *  PI);
    if (engineRpm < 1000.0f) engineRpm = 1000.0f;
    if (engineRpm > 7500.0f) engineRpm = 7500.0f;

    if (data.automaticTransmission) {
        if (engineRpm >= 6100.0f && selectedGear < 5) {
            selectedGear++;
        } else if (engineRpm <= 1200.0f && selectedGear > 0) {
            selectedGear--;
        }
    }

    float engineTorque = lookupTorque(engineRpm);   // get torque at specific rpm value

    // user input
    float gasInput = Input::isKeyDown(GLFW_KEY_W) ? 1.0f : 0.0f;
    if (Input::isKeyDown(GLFW_KEY_D)) steeringAngle = -10.0f;
    if (Input::isKeyDown(GLFW_KEY_A)) steeringAngle = 10.0f;
    brakeForce.x = Input::isKeyDown(GLFW_KEY_SPACE) ? -10000.0f : 0.0f;

    float wheelTorque = engineTorque * data.gearRatios[selectedGear] * data.finalRatio * gasInput;  // calculate torque on wheels based on engine torque

    slipAngleFront = atan2(velCar.z + angularVel * data.weightRatio * data.wheelBase, abs(velCar.x)) - sign(velCar.x) * glm::radians(steeringAngle);
    slipAngleRear = atan2(velCar.z - angularVel * (1 - data.weightRatio) * data.wheelBase, abs(velCar.x));

    latForceFront = weightFront * pacejka(slipAngleFront);
    latForceRear = weightRear * pacejka(slipAngleRear);

    angularTorque = latForceFront * data.weightRatio * data.wheelBase - latForceRear * (1 - data.weightRatio) * data.wheelBase;

    tractionForce.x = wheelTorque / wheel_bl->getRadius();
    lateralForce = cos(glm::radians(steeringAngle)) * latForceFront + latForceRear;
    dragForce = glm::length(velCar) * velCar * -data.dragConstant;
    rollForce = velCar * -data.rollConstant; 

    angularTorque += rollForce.z;

    totalForce = tractionForce + dragForce + rollForce + brakeForce;
    totalForce.z += lateralForce;

    accelCar = totalForce / data.mass;

    // translate back to world coords
    accel.x = cs * accelCar.x - sn * accelCar.z;
    accel.z = sn * accelCar.x + cs * accelCar.z;

    vel += dt * accel;
    pos += dt * vel;

    angularAccel = angularTorque / data.mass;
    angularVel += angularAccel * dt;
    yaw += angularVel * dt;
}


float Car::lookupTorque(float rpm) {
    float torque = data.torqueCurve[0];
    for (uint32_t i = 1; i < data.rpmCurve.size(); i++) {
        if (rpm > data.rpmCurve[i-1] && rpm < data.rpmCurve[i]) {
            torque = lerp(data.torqueCurve[i-1], data.torqueCurve[i], ((rpm - data.rpmCurve[i-1]) / (data.rpmCurve[i] - data.rpmCurve[i-1])));
        }
    }

    return torque;
}


void Car::gui() {
    ImGui::Begin("car");
    ImGui::Text("accel =  %.1f %.1f %.1f", accel.x, accel.y, accel.z);
    ImGui::Text("vel =  %.1f %.1f %.1f", vel.x, vel.y, vel.z);
    ImGui::Text("pos =  %.1f %.1f %.1f", pos.x, pos.y, pos.z);
    ImGui::NewLine();
    ImGui::Text("localAccel = %.1f %.1f", accelCar.x, accelCar.z);
    ImGui::Text("localVel = %.1f %.1f", velCar.x, velCar.z);
    ImGui::NewLine();
    ImGui::Text("total force =  %.1f, %.1f, %.1f", totalForce.x, totalForce.y, totalForce.z);
    ImGui::Text("roll =  %.1f %.1f", rollForce.x, rollForce.z);
    ImGui::Text("drag =  %.1f %.1f", dragForce.x, dragForce.z);
    ImGui::Text("weight front = %.2f", weightFront);
    ImGui::Text("weight rear = %.2f", weightRear);
    ImGui::Text("lat front = %.2f", latForceFront);
    ImGui::Text("lat rear = %.2f", latForceRear);
    ImGui::Text("slip front = %.2f", slipAngleFront);
    ImGui::Text("slip rear = %.2f", slipAngleRear);
    ImGui::Text("torque = %.2f", angularTorque);
    ImGui::Text("yaw = %.2f", yaw);
    ImGui::SliderFloat("steering", &steeringAngle, -40.0f, 40.0f);
    ImGui::End();

    ImGui::Begin("engine");
    ImGui::Text("rpm = %.0f", engineRpm);
    ImGui::Text("gear = %u", selectedGear + 1);
    ImGui::End();

    {
        // extremely bad graph code pls dont look
        ImGui::Begin("graphs");

        static float startTime = glfwGetTime();
        static uint32_t count = 10000;
        static float timeData[1000] = {};

        static float rpm[1001] = {};
        static float rollX[1001] = {};
        static float rollZ[1001] = {};
        static float dragX[1001] = {};
        static float dragZ[1001] = {};
        static float latRear[1001] = {};
        static float latFront[1001] = {};
        static float tractionX[1001] = {};
        static float slipFrontData[1001] = {};
        static float slipRearData[1001] = {};

        if (ImGui::Button("start graph")) {
            count = 0;
            startTime = glfwGetTime();
        }

        if (count < 10000) {
            count++;
            if (count % 10 == 0) {
                timeData[count/10] = glfwGetTime() - startTime;
                rpm[count/10] = engineRpm;
                rollX[count/10] = rollForce.x;
                rollZ[count/10] = rollForce.z;
                dragX[count/10] = dragForce.x;
                dragZ[count/10] = dragForce.z;
                tractionX[count/10] = tractionForce.x;
                slipFrontData[count/10] = slipAngleFront;
                slipRearData[count/10] = slipAngleRear;
                latRear[count/10] = latForceRear;
                latFront[count/10] = latForceFront;
            }
        }

        if (ImPlot::BeginPlot("rpm")) {
            ImPlot::SetupAxes("time", "rpm", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::PlotLine("rpm", timeData, rpm, count/10);
            ImPlot::EndPlot();
        }

        if (ImPlot::BeginPlot("slip angles")) {
            ImPlot::SetupAxes("time", "", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::PlotLine("front", timeData, slipFrontData, count/10);
            ImPlot::PlotLine("rear", timeData, slipRearData, count/10);
            ImPlot::EndPlot();
        }

        if (ImPlot::BeginPlot("longitudinal forces")) {
            ImPlot::SetupAxes("time", "force (N)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::PlotLine("air resistance", timeData, dragX, count/10);
            ImPlot::PlotLine("roll resistance", timeData, rollX, count/10);
            ImPlot::PlotLine("traction", timeData, tractionX, count/10);
            ImPlot::EndPlot();
        }

        if (ImPlot::BeginPlot("lateral forces")) {
            ImPlot::SetupAxes("time", "force (N)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::PlotLine("air resistance", timeData, dragZ, count/10);
            ImPlot::PlotLine("roll resistance", timeData, rollZ, count/10);
            ImPlot::PlotLine("rear wheels", timeData, latRear, count/10);
            ImPlot::PlotLine("front wheels", timeData, latFront, count/10);
            ImPlot::EndPlot();
        }

        ImGui::End();
    }
}
