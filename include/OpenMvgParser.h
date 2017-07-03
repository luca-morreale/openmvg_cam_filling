/*
 * OpenMvgParser.h
 *
 *  Created on: 16 mar 2016
 *      Author: andrea
 */

#ifndef JSON_CAM_FILLING_OPENMVG_PARSER_H_
#define JSON_CAM_FILLING_OPENMVG_PARSER_H_

#include <fstream>
#include <iostream>

#include <aliases.h>
#include <Exceptions.hpp>

namespace jsonfill {

    class OpenMvgParser {
    public:
        OpenMvgParser(std::string path);
        virtual ~OpenMvgParser();
        virtual void parse(std::string path);
        virtual void parse();
        virtual void saveChanges(std::string newFilename);
        virtual void setCamPosition(int camIndex, GLMVec3 &camCenter, GLMMat3 rotation=GLMMat3());  // cam index = image index
        virtual GLMVec3 getCamPosition(int camIndex);
        virtual bool testCamPosition(int camIndex, GLMVec3 &camCenter);

        void setFile(std::string path);

    protected:
        virtual void checkViews();
        virtual void checkIntrinsics();
        virtual void checkExtrinsics();
        virtual void checkPoints();
        virtual void checkCameraExistence(int camIndex);

        int getCameraRef(int camIndex);

        void addFieldToDocuemnt(std::string name, JsonValue &content);
        void addFieldTo(JsonValue &parent, std::string name, JsonValue &content);
        void addExtrinsicMember();
        void pushBackTo(JsonValue &array, JsonValue &content);
        void pushBackTo(JsonValue &array, double value, int n);
        void addCameraToExtrinsic(int camIndex);

    private:
        JsonDoc document;
        std::string fileName;
        std::ifstream cin;
        
    };

} // jsonfill

#endif /* JSON_CAM_FILLING_OPENMVG_PARSER_H_ */
