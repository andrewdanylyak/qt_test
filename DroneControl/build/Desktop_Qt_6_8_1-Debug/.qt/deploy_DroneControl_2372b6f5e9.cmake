include(/home/msi/Repos/QtProjects/DroneControl/build/Desktop_Qt_6_8_1-Debug/.qt/QtDeploySupport.cmake)
include("${CMAKE_CURRENT_LIST_DIR}/DroneControl-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/msi/Repos/QtProjects/DroneControl/build/Desktop_Qt_6_8_1-Debug/DroneControl
    GENERATE_QT_CONF
)
