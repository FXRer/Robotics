IF (EXISTS ${PROJECT_SOURCE_DIR}/.svn)
	INCLUDE(${OpenRDK_CMAKE_MODULE_PATH}/FindSubversion.cmake)
	IF(Subversion_FOUND)
		Subversion_WC_INFO(${PROJECT_SOURCE_DIR} PROJECT)
		# Workaround for wrong retrieved information
		STRING(LENGTH ${PROJECT_WC_REVISION} tmpSVNINFO)
		IF(${tmpSVNINFO} GREATER 10)
			SET(PROJECT_WC_REVISION "0")
		ENDIF(${tmpSVNINFO} GREATER 10)
		string(REGEX MATCH ".*/openrdk/branches/.*" __is_branch ${PROJECT_WC_URL})
		set(PROJECT_CODENAME "trunk")
		if (NOT "x${__is_branch}" STREQUAL "x")
			string(REGEX REPLACE ".*/([^/]*)" "\\1" __dirname ${PROJECT_SOURCE_DIR})
			string(REGEX REPLACE ".*/openrdk/branches/.*-(.*)/${__dirname}" "\\1" PROJECT_CODENAME ${__is_branch})
		endif (NOT "x${__is_branch}" STREQUAL "x")
	ENDIF(Subversion_FOUND)
ENDIF (EXISTS ${PROJECT_SOURCE_DIR}/.svn)

info("-- Current SVN revision is ${PROJECT_WC_REVISION} (codename: ${PROJECT_CODENAME})")
