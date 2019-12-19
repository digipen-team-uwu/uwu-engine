#Populate headers
file(GLOB_RECURSE HEADER *.h)
file(GLOB_RECURSE HPP_HEADER *.hpp)

set(HEADERS
        ${HEADER}
        ${HPP_HEADER}

        PARENT_SCOPE
)
