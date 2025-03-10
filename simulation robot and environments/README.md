# Barrett-7dof-WAM-gazebo-moveit

## 一、编译Build

### 安装所需的ros库：
```
# FOR UBUNTU 20
sudo apt install ros-noetic-joint-state-controller ros-noetic-moveit  ros-noetic-robot-state-publisher  ros-noetic-effort-controllers ros-noetic-joint-trajectory-controller ros-noetic-gripper-action-controller

# FOR UBUNTU 18
sudo apt install ros-melodic-joint-state-controller ros-melodic-moveit  ros-melodic-robot-state-publisher  ros-melodic-effort-controllers ros-melodic-joint-trajectory-controller ros-melodic-gripper-action-controller
```


### 创建工作空间：
```mkdir -p {ROS_WORKSPACE}/src```

### 下载：
```cd {ROS_WORKSPACE}/src```

```git clone https://github.com/TINY-KE/Barrett-7dof-WAM-arm-gazebo-moveit.git```

### 编译
```
cd {ROS_WORKSPACE}

catkin_make
```


## 二、运行Run
### 添加工作空间的路径

``` cd {ROS_WORKSPACE} ```

```source devel/setup.bash ```

### 在gazebo中可视化机器人urdf模型
+ 启动一个空白的gazebo环境

```roslaunch    barrett_model  create_world.launch  ```

+ 往gazebo中添加机器人，注意修改view_urdf.launch文件中的机器人模型

```roslaunch    barrett_model view_urdf.launch  ```


### 启动仿真环境（末端为相机）

+ 对应机器人模型 debug2_wam_7dof_wam_bhand.urdf.xacro

```roslaunch    wam_arm_moveit    wam_kinectv1_bringup_moveit_onlyrobot.launch ```

### 启动仿真环境（差速底盘+机械臂+末端相机）

+ 对应机器人模型 mobile_7dof_wam_kinectv1.urdf.xacro

 ```roslaunch mobile_wam_arm_moveit mobile_wam_kinectv1_bringup_moveit_onlyrobot.launch ```

 注：这里的轮子还是外显的，在最终做完实验之后，可以将mobile_chassis.urdf.xacro中动力轮和支撑轮的visual属性删除，以使得展示效果更好。


### 待实现： 启动仿真环境（末端为抓手）
+ 对应机器人模型 debug3_wam_7dof_wam_bhand.urdf.xacro

```roslaunch    wam_arm_moveit    wam_hand_bringup_moveit_onlyrobot.launch ```

