IF ("${CMAKE_CROSSCOMPILING}" STREQUAL "TRUE" OR "${CMAKE_CROSSCOMPILING}" STREQUAL "ON")

	IF ("${OpenRDK_ARCH}" STREQUAL "geode" )
		INCLUDE(${OE_CMAKE_MODULE_PATH}/xml2-config.cmake) 
		SET(LIBXML2_FOUND ${XML2_PACKAGE_FOUND})
		#SET(LIBXML2_FOUND ${XML2_FOUND})
		SET(LIBXML2_INCLUDE_DIR "${XML2_INCLUDE_DIRS}")
		SET(LIBXML2_LIBRARIES "${XML2_LIBRARIES}")
	ELSEIF ("${OpenRDK_ARCH}" STREQUAL "atom" )
			INCLUDE(${OE_CMAKE_MODULE_PATH}/xml2-config.cmake)
			SET(LIBXML2_FOUND ${XML2_PACKAGE_FOUND})
			#SET(LIBXML2_FOUND ${XML2_FOUND})
			SET(LIBXML2_INCLUDE_DIR "${XML2_INCLUDE_DIRS}")
			SET(LIBXML2_LIBRARIES "${XML2_LIBRARIES}")
	ELSEIF ("${OpenRDK_ARCH}" STREQUAL "arm9" )
			SET(LIBXML2_FOUND 1)
			SET(LIBXML2_INCLUDE_DIR "${ARM9_CROSS_ADDONS_DIR}/include/libxml2")
			SET(LIBXML2_LIBRARIES xml2)
	ELSEIF ("${OpenRDK_ARCH}" STREQUAL "geode" )
		MESSAGE(STATUS "LibXML2 support is not available for unknown architecture [${OpenRDK_ARCH}]")
	ENDIF ("${OpenRDK_ARCH}" STREQUAL "geode" )

ELSE ("${CMAKE_CROSSCOMPILING}" STREQUAL "TRUE" OR "${CMAKE_CROSSCOMPILING}" STREQUAL "ON")
	FIND_PACKAGE(LibXml2 REQUIRED)
ENDIF ("${CMAKE_CROSSCOMPILING}" STREQUAL "TRUE" OR "${CMAKE_CROSSCOMPILING}" STREQUAL "ON")