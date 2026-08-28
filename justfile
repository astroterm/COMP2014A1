cxx := "c++"
cxx_ver := "20"
flags := "-std=c++" + cxx_ver + " -Wall -Wextra -pedantic"

run source="*.cpp": (build source)
    target/main

build source="*.cpp":
    {{cxx}} {{flags}} src/{{source}} -o "target/main"

