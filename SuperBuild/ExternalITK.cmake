set( proj ITK )
set( ITK_REPOSITORY https://github.com/InsightSoftwareConsortium/ITK.git )
set( ITK_TAG "v${ITK_VERSION_STRING}")

ExternalProject_Add( ${proj}
  GIT_REPOSITORY ${ITK_REPOSITORY}
  GIT_TAG ${ITK_TAG}
  UPDATE_COMMAND ""
  SOURCE_DIR ${proj}
  BINARY_DIR ${proj}-build
  CMAKE_ARGS
    --no-warn-unused-cli
    -DBUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DITK_BUILD_DEFAULT_MODULES:BOOL=ON
    -DModule_ITKReview:BOOL=ON
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
    -DCMAKE_SKIP_RPATH:BOOL=ON
    -DITK_LEGACY_REMOVE:BOOL=ON
    -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property( ITK install_dir )
set( ITK_DIR "${install_dir}/lib/cmake/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}" )