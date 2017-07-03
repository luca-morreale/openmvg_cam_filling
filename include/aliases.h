#ifndef JSON_CAM_FILLING_ALIASES_H
#define JSON_CAM_FILLING_ALIASES_H


#include <map>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

#include <glm/glm.hpp>


namespace jsonfill {


    typedef glm::vec3 GLMVec3;
    typedef glm::mat3 GLMMat3;


    typedef rapidjson::SizeType JsonSizeT;
    const auto JsonArray = rapidjson::kArrayType;
    const auto JsonObject = rapidjson::kObjectType;
    const auto JsonNumber = rapidjson::kNumberType;

    typedef rapidjson::Document JsonDoc;
    typedef rapidjson::Value JsonValue;
    typedef rapidjson::IStreamWrapper JsonFINWrapper;
    typedef rapidjson::OStreamWrapper JsonFOUTWrapper;
    typedef rapidjson::Writer<JsonFOUTWrapper> JsonWriter;
    typedef rapidjson::PrettyWriter<JsonFOUTWrapper> JsonPrettyWriter;

} // jsonfill

#endif // JSON_CAM_FILLING_ALIASES_H
