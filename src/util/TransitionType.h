//
// Created by vitor on 10/20/24.
//

#ifndef TRANSITIONTYPE_H
#define TRANSITIONTYPE_H
#include <string>
#include <unordered_map>


namespace pk {

    enum TransitionType {
        HospitalTransition,
        FireArenaTransition,
        PlantArenaTransition,
        WaterArenaTransition,
        HouseTransition
    };

    const static std::unordered_map<std::string, pk::TransitionType> stringToTransitionType = {
        {"House", pk::HouseTransition},
        {"Hospital", pk::HospitalTransition},
        {"Fire-Arena", pk::FireArenaTransition},
        {"Water-Arena", pk::WaterArenaTransition},
        {"Plant-Arena", pk::PlantArenaTransition}
    };

    const static std::unordered_map<pk::TransitionType, std::string> transitionTypeToString = {
        {pk::HouseTransition, "House"},
        {pk::HospitalTransition, "Hospital"},
        {pk::FireArenaTransition, "Fire-Arena"},
        {pk::WaterArenaTransition, "Water-Arena"},
        {pk::PlantArenaTransition, "Plant-Arena"}
    };

}

#endif //TRANSITIONTYPE_H
