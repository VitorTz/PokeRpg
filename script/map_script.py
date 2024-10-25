import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer, TiledObjectGroup, TiledObject
from enum import Enum, auto


class MapId(Enum):

    World = auto()
    Hospital = auto()


MAPS = {
    MapId.World: ("../src/assets/data/maps/world.tmx", "../src/assets/data/maps/world.txt"),
    MapId.Hospital: ("../src/assets/data/maps/hospital.tmx", "../src/assets/data/maps/hospital.txt"),
}


def main() -> None:
    display = pygame.display.set_mode((200, 200))
    pygame.display.set_caption("TiledMap")
    map_id = MapId.World

    tiled_map: TiledMap = load_pygame(MAPS[map_id][0])
    output_file = MAPS[map_id][1]
    
    with open(output_file, "w+") as file:
        for i in tiled_map:
            if (isinstance(i, TiledObjectGroup)):
                i: TiledObjectGroup
                file.write(f"{i.name}\n")
                file.write(f"{len(i)} {i.properties['mId']}\n")
                for tile in i:
                    tile: TiledObject
                    line = f"{tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f} "
                    line += str(tile.properties.get("mId", -1))
                    line = line.strip() + " "
                    line += tile.properties.get("source", "").replace("../tilesets/../../", "")
                    file.write(f"{line.strip()}\n")


if __name__ == "__main__":
    main()
