IF(MagickPP_FOUND)
	INCLUDE_DIRECTORIES(${MagickPP_INCLUDE_DIR})
	LINK_DIRECTORIES(${MagickPP_LINK_DIRECTORIES})
ENDIF(MagickPP_FOUND)
RDK_ADD_RAGENT_MODULE(ALL_FILES)
IF(MagickPP_FOUND)
	TARGET_LINK_LIBRARIES(${RDK_THIS_MODULE_NAME} ${MagickPP_LIBRARIES})
ENDIF(MagickPP_FOUND)

