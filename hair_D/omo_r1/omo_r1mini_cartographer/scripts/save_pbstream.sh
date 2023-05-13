#!/bin/bash
rosservice call /finish_trajectory 0
rosservice call /write_state "{filename: '${HOME}/Downloads/map.pbstream'}" 
echo "Map saved to ${HOME}/Downloads/map.pbstream"