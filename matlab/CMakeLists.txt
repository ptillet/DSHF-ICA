foreach(F neo_ica)
        matlab_add_mex(NAME ${F}_mex SRC ${F}.cpp LINK_TO neo_ica ${Matlab_LIBRARIES} ${Matlab_BLAS_LIBRARY} ${Matlab_LAPACK_LIBRARY})
        set_target_properties(${F}_mex PROPERTIES OUTPUT_NAME ${F})
        #installation
        set(DEST "${Matlab_ROOT_DIR}/toolbox/neo_ica/")
        install(TARGETS ${F}_mex ARCHIVE DESTINATION ${DEST} LIBRARY DESTINATION ${DEST})
endforeach()
