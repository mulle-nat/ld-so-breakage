cmake_minimum_required(VERSION 3.0)

project( mistaken C)


add_library( lib_a SHARED
src/a.c
)

add_library( lib_b SHARED
src/b.c
)

add_library( lib_c STATIC
src/c.c
)

add_library( lib_d SHARED
src/d.c
)

add_library( lib_e SHARED
src/e.c
)



add_dependencies( lib_a lib_e)
target_link_libraries( lib_a
lib_e
)

add_dependencies( lib_b lib_e)
target_link_libraries( lib_b
lib_e
)

add_dependencies( lib_d lib_b)
target_link_libraries( lib_d
lib_b
)

if( APPLE)
   target_link_libraries( lib_a "-undefined dynamic_lookup")
   target_link_libraries( lib_b "-undefined dynamic_lookup")
   target_link_libraries( lib_d "-undefined dynamic_lookup")
   target_link_libraries( lib_e "-undefined dynamic_lookup")
else()
   set( AS_NEEDED -Wl,--as-needed)
   set( NO_AS_NEEDED -Wl,--no-as-needed)
endif()


##
## The linux linker is extemely picky about the order of the linked files.
## That would be nice if it then didn't reorder the files as it seems
## fit... sometimes... non-deterministic... &"%!!"
##


##
## A ? ? ?
##

# add_executable( main_abcd
# src/main.c
# )
#
# add_dependencies( main_abcd lib_b lib_c lib_d)
#
# target_link_libraries( main_abcd
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_abdc
# src/main.c
# )
#
# add_dependencies( main_abdc lib_b lib_c lib_d)
#
# target_link_libraries( main_abdc
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# )
#
#
# add_executable( main_acbd
# src/main.c
# )
#
# add_dependencies( main_acbd lib_b lib_c lib_d)
#
# target_link_libraries( main_acbd
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_acdb
# src/main.c
# )
#
# add_dependencies( main_acdb lib_b lib_c lib_d)
#
# target_link_libraries( main_acdb
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# lib_b
# )

add_executable( main_adbc
src/main.c
)

add_dependencies( main_adbc lib_b lib_c lib_d)

target_link_libraries( main_adbc
${NO_AS_NEEDED} lib_a ${AS_NEEDED}
${NO_AS_NEEDED} lib_d ${AS_NEEDED}
lib_b
${NO_AS_NEEDED} lib_c ${AS_NEEDED}
)


# add_executable( main_adcb
# src/main.c
# )
#
# add_dependencies( main_adcb lib_b lib_c lib_d)
#
# target_link_libraries( main_adcb
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# )

##
## B ? ? ?
##

# add_executable( main_bacd
# src/main.c
# )
#
# add_dependencies( main_bacd lib_b lib_c lib_d)
#
# target_link_libraries( main_bacd
# lib_b
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_badc
# src/main.c
# )
#
# add_dependencies( main_badc lib_b lib_c lib_d)
#
# target_link_libraries( main_badc
# lib_b
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# )
#
#
# add_executable( main_bcad
# src/main.c
# )
#
# add_dependencies( main_bcad lib_b lib_c lib_d)
#
# target_link_libraries( main_bcad
# lib_b
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_bcda
# src/main.c
# )
#
# add_dependencies( main_bcda lib_b lib_c lib_d)
#
# target_link_libraries( main_bcda
# lib_b
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# )
#
# add_executable( main_bdac
# src/main.c
# )
#
# add_dependencies( main_bdac lib_b lib_c lib_d)
#
# target_link_libraries( main_bdac
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# )
#
#
# add_executable( main_bdca
# src/main.c
# )
#
# add_dependencies( main_bdca lib_b lib_c lib_d)
#
# target_link_libraries( main_bdca
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# )


##
## C ? ? ?
##

# add_executable( main_cabd
# src/main.c
# )
#
# add_dependencies( main_cabd lib_b lib_c lib_d)
#
# target_link_libraries( main_cabd
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_cadb
# src/main.c
# )
#
# add_dependencies( main_cadb lib_b lib_c lib_d)
#
# target_link_libraries( main_cadb
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# lib_b
# )
#
#
# add_executable( main_cbad
# src/main.c
# )
#
# add_dependencies( main_cbad lib_b lib_c lib_d)
#
# target_link_libraries( main_cbad
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# )
#
#
# add_executable( main_cbda
# src/main.c
# )
#
# add_dependencies( main_cbda lib_b lib_c lib_d)
#
# target_link_libraries( main_cbda
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# )
#
# add_executable( main_cdab
# src/main.c
# )
#
# add_dependencies( main_cdab lib_b lib_c lib_d)
#
# target_link_libraries( main_cdab
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# lib_b
# )
#
# add_executable( main_cdba
# src/main.c
# )
#
# add_dependencies( main_cdba lib_b lib_c lib_d)
#
# target_link_libraries( main_cdba
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# )


##
## D ? ? ?
##

add_executable( main_dabc
src/main.c
)

add_dependencies( main_dabc lib_b lib_c lib_d)

target_link_libraries( main_dabc
${NO_AS_NEEDED} lib_d ${AS_NEEDED}
${NO_AS_NEEDED} lib_a ${AS_NEEDED}
lib_b
${NO_AS_NEEDED} lib_c ${AS_NEEDED}
)


# add_executable( main_dacb
# src/main.c
# )
#
# add_dependencies( main_dacb lib_b lib_c lib_d)
#
# target_link_libraries( main_dacb
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# )


add_executable( main_dbac
src/main.c
)

add_dependencies( main_dbac lib_b lib_c lib_d)

target_link_libraries( main_dbac
${NO_AS_NEEDED} lib_d ${AS_NEEDED}
lib_b
${NO_AS_NEEDED} lib_a ${AS_NEEDED}
${NO_AS_NEEDED} lib_c ${AS_NEEDED}
)


add_executable( main_dbca
src/main.c
)

add_dependencies( main_dbca lib_b lib_c lib_d)

target_link_libraries( main_dbca
${NO_AS_NEEDED} lib_d ${AS_NEEDED}
lib_b
${NO_AS_NEEDED} lib_c ${AS_NEEDED}
${NO_AS_NEEDED} lib_a ${AS_NEEDED}
)

# add_executable( main_dcab
# src/main.c
# )
#
# add_dependencies( main_dcab lib_b lib_c lib_d)
#
# target_link_libraries( main_dcab
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# lib_b
# )
#
#
# add_executable( main_dcba
# src/main.c
# )
#
# add_dependencies( main_dcba lib_b lib_c lib_d)
#
# target_link_libraries( main_dcba
# ${NO_AS_NEEDED} lib_d ${AS_NEEDED}
# ${NO_AS_NEEDED} lib_c ${AS_NEEDED}
# lib_b
# ${NO_AS_NEEDED} lib_a ${AS_NEEDED}
# )

