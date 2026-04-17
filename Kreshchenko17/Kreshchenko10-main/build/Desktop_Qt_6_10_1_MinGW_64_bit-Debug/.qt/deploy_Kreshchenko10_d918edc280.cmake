include("F:/qtdz/Kreshchenko10/build/Desktop_Qt_6_10_1_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Kreshchenko10-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "F:/qtdz/Kreshchenko10/build/Desktop_Qt_6_10_1_MinGW_64_bit-Debug/Kreshchenko10.exe"
    GENERATE_QT_CONF
)
