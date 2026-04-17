include("F:/qtdz/Kreshchenko16/build/Desktop_Qt_6_10_1_MinGW_64_bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/Kreshchenko16-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "F:/qtdz/Kreshchenko16/build/Desktop_Qt_6_10_1_MinGW_64_bit-Debug/Kreshchenko16.exe"
    GENERATE_QT_CONF
)
