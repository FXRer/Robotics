IF(V4L2_FOUND)
	INCLUDE_DIRECTORIES(${V4L2_INCLUDE_DIR})
	LINK_DIRECTORIES(${V4L2_LINK_DIRECTORIES})
	IF(libv4l2_FOUND)
		INCLUDE_DIRECTORIES(${libv4l2_INCLUDE_DIR})
		LINK_DIRECTORIES(${libv4l2_LINK_DIRECTORIES})
	ENDIF(libv4l2_FOUND)
	RDK_ADD_RAGENT_MODULE(ALL_FILES)
	TARGET_LINK_LIBRARIES(${RDK_THIS_MODULE_NAME} "${V4L2_LIBRARIES}")
	IF(libv4l2_FOUND)
		TARGET_LINK_LIBRARIES(${RDK_THIS_MODULE_NAME} "${libv4l2_LIBRARIES}")
	ENDIF(libv4l2_FOUND)
ENDIF(V4L2_FOUND)
