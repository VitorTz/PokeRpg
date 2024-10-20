import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer, TiledObjectGroup, TiledObject
from enum import Enum, auto


class MapId(Enum):

    World = auto()


MAPS = {
    MapId.World: ("../src/assets/data/maps/world.tmx", "../src/assets/data/maps/world.txt")
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
                file.write(f"{len(i)}\n")
                try:
                    line = ""
                    for tile in i:
                        tile: TiledObject                                     
                        line = f"{tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f}"                                                

                        try:
                            match i.name:
                                case "Sprites" | "Trees" | "Houses" | "Arena" | "Hospital":
                                    line += " " + tile.properties["source"].replace("../tilesets/../../", "./assets/")
                                case "Houses" | "Arena" | "Hospital" | "Transition":
                                    line += " " + tile.name
                        except Exception:
                            pass
                            
                        line += '\n'
                        file.write(line)
                except Exception as e:
                    print(f"Exception -> TileGroup={i.name} | properties={tile.properties} | x={tile.x} | y={tile.y}", e)

                


if __name__ == "__main__":
    main()
