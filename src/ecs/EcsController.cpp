#include "EcsController.hpp"


std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsController::ecs_t>> pk::EcsController::ecsInstanceMap{};
pk::EcsController::ecs_t* pk::EcsController::ecs{nullptr};
pk::MapId pk::EcsController::currentMapId{};
