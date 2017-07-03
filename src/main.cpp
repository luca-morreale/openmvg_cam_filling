
#include <cmath>
#include <iostream>
#include <fstream>

#include <OpenMvgParser.h>

#include <rapidjson/document.h>

glm::vec3 computeAngles(glm::vec3 &p, glm::vec3 &la);
glm::mat3 getRotationMatrix(float roll, float pitch, float yaw);

int main(int argc, char **argv) {

    if (argc < 3) {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " openmvg.json cam_positions.txt" << std::endl;
        std::cout << "cam_positions.txt format: index cam_x cam_y cam_z lookat_x lookat_y lookat_z" << std::endl;
        return 1;
    }

    std::string jsonFile = argv[1];
    std::string camPosFile = argv[2];
    std::string outFile = jsonFile.substr(0, jsonFile.find_last_of(".")) + "_known.json";

    std::cout << jsonFile << " " << camPosFile << " " << outFile << std::endl;

    std::ifstream cin(camPosFile);

    jsonfill::OpenMvgParser parser(jsonFile);
    parser.parse();

    int camIndex;
    glm::vec3 camPos;
    glm::vec3 lookat;

    // NOTE:
    // openMVG_main_ComputeStructureFromKnownPoses requires both intrinsic and extrinsics parameters
    // intrinsic given from previous phases, extrinsics computed from pose and lookat

    while(!cin.eof()) {
        cin >> camIndex >> camPos.x >> camPos.y >> camPos.z >> lookat.x >> lookat.y >> lookat.z ;

        glm::vec3 angles = computeAngles(camPos, lookat);
        glm::mat3 rotation = getRotationMatrix(angles.x, angles.y, angles.z);

        parser.setCamPosition(camIndex, camPos, rotation);
    }
    cin.close();

    std::cout << "closing\n";

    parser.saveChanges(outFile);


    return 0;
}

glm::vec3 computeAngles(glm::vec3 &p, glm::vec3 &la) {
    glm::vec3 v = p - la;

    glm::vec3 angles;
    angles.z = std::atan2(v[0], -v[2]);                             // yaw
    angles.y = std::atan2(std::sqrt(v[0]*v[0] + v[1]*v[1]), v[2]);  // pitch
    angles.x = 0;                                                   // roll asssumed to be zero

    return angles;
}

glm::mat3 getRotationMatrix(float roll, float pitch, float yaw) {
    // Calculate rotation about x axis
    glm::mat3 Rx = glm::mat3(1, 0, 0, 
                            0, std::cos(roll), -std::sin(roll),
                            0, std::sin(roll), std::cos(roll));
    // Calculate rotation about y axis
    glm::mat3 Ry = glm::mat3(std::cos(pitch), 0, std::sin(pitch), 
                            0, 1, 0,
                            -std::sin(pitch), 0, std::cos(pitch));
    // Calculate rotation about z axis
    glm::mat3 Rz = glm::mat3(std::cos(yaw), -std::sin(yaw), 0, 
                            std::sin(yaw), std::cos(yaw), 0,
                            0, 0, 1);
    return (Rz * Ry) * Rx;
}
