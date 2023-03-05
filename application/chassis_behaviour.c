  /**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       chassis_behaviour.c/h
  * @brief      according to remote control, change the chassis behaviour.
  *             ¸ù¾ÝÒ£¿ØÆ÷µÄÖµ£¬¾ö¶¨µ×ÅÌÐÐÎª¡£
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. done
  *  V1.1.0     Nov-11-2019     RM              1. add some annotation
  *
  @verbatim
  ==============================================================================
    add a chassis behaviour mode
    1. in chassis_behaviour.h , add a new behaviour name in chassis_behaviour
    erum
    {  
        ...
        ...
        CHASSIS_XXX_XXX, // new add
    }chassis_behaviour_e,
    2. implement new function. chassis_xxx_xxx_control(fp32 *vx, fp32 *vy, fp32 *wz, chassis_move_t * chassis )
        "vx, vy, wz" param is chassis movement contorl input. 
        first param: 'vx' usually means  vertical speed,
            positive value means forward speed, negative value means backward speed.
        second param: 'vy' usually means horizotal speed,
            positive value means letf speed, negative value means right speed
        third param: 'wz' can be rotation speed set or angle set, 

        in this new function, you can assign speed to "vx","vy",and "wz",as your wish
    3.  in "chassis_behaviour_mode_set" function, add new logical judgement to assign CHASSIS_XXX_XXX to  "chassis_behaviour_mode" variable,
        and in the last of the function, add "else if(chassis_behaviour_mode == CHASSIS_XXX_XXX)" 
        choose a chassis control mode.
        four mode:
        CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW : 'vx' and 'vy' are speed control, 'wz' is angle set to control relative angle
            between chassis and gimbal. you can name third param to 'xxx_angle_set' other than 'wz'
        CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW : 'vx' and 'vy' are speed control, 'wz' is angle set to control absolute angle calculated by gyro
            you can name third param to 'xxx_angle_set.
        CHASSIS_VECTOR_NO_FOLLOW_YAW : 'vx' and 'vy' are speed control, 'wz' is rotation speed control.
        CHASSIS_VECTOR_RAW : will use 'vx' 'vy' and 'wz'  to linearly calculate four wheel current set, 
            current set will be derectly sent to can bus.
    4. in the last of "chassis_behaviour_control_set" function, add
        else if(chassis_behaviour_mode == CHASSIS_XXX_XXX)
        {
            chassis_xxx_xxx_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
        }

        
    Èç¹ûÒªÌí¼ÓÒ»¸öÐÂµÄÐÐÎªÄ£Ê½
    1.Ê×ÏÈ£¬ÔÚchassis_behaviour.hÎÄ¼þÖÐ£¬ Ìí¼ÓÒ»¸öÐÂÐÐÎªÃû×ÖÔÚ chassis_behaviour_e
    erum
    {  
        ...
        ...
        CHASSIS_XXX_XXX, // ÐÂÌí¼ÓµÄ
    }chassis_behaviour_e,

    2. ÊµÏÖÒ»¸öÐÂµÄº¯Êý chassis_xxx_xxx_control(fp32 *vx, fp32 *vy, fp32 *wz, chassis_move_t * chassis )
        "vx,vy,wz" ²ÎÊýÊÇµ×ÅÌÔË¶¯¿ØÖÆÊäÈëÁ¿
        µÚÒ»¸ö²ÎÊý: 'vx' Í¨³£¿ØÖÆ×ÝÏòÒÆ¶¯,ÕýÖµ Ç°½ø£¬ ¸ºÖµ ºóÍË
        µÚ¶þ¸ö²ÎÊý: 'vy' Í¨³£¿ØÖÆºáÏòÒÆ¶¯,ÕýÖµ ×óÒÆ, ¸ºÖµ ÓÒÒÆ
        µÚÈý¸ö²ÎÊý: 'wz' ¿ÉÄÜÊÇ½Ç¶È¿ØÖÆ»òÕßÐý×ªËÙ¶È¿ØÖÆ
        ÔÚÕâ¸öÐÂµÄº¯Êý, ÄãÄÜ¸ø "vx","vy",and "wz" ¸³ÖµÏëÒªµÄËÙ¶È²ÎÊý
    3.  ÔÚ"chassis_behaviour_mode_set"Õâ¸öº¯ÊýÖÐ£¬Ìí¼ÓÐÂµÄÂß¼­ÅÐ¶Ï£¬¸øchassis_behaviour_mode¸³Öµ³ÉCHASSIS_XXX_XXX
        ÔÚº¯Êý×îºó£¬Ìí¼Ó"else if(chassis_behaviour_mode == CHASSIS_XXX_XXX)" ,È»ºóÑ¡ÔñÒ»ÖÖµ×ÅÌ¿ØÖÆÄ£Ê½
        4ÖÖ:
        CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW : 'vx' and 'vy'ÊÇËÙ¶È¿ØÖÆ£¬ 'wz'ÊÇ½Ç¶È¿ØÖÆ ÔÆÌ¨ºÍµ×ÅÌµÄÏà¶Ô½Ç¶È
        Äã¿ÉÒÔÃüÃû³É"xxx_angle_set"¶ø²»ÊÇ'wz'
        CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW : 'vx' and 'vy'ÊÇËÙ¶È¿ØÖÆ£¬ 'wz'ÊÇ½Ç¶È¿ØÖÆ µ×ÅÌµÄÍÓÂÝÒÇ¼ÆËã³öµÄ¾ø¶Ô½Ç¶È
        Äã¿ÉÒÔÃüÃû³É"xxx_angle_set"
        CHASSIS_VECTOR_NO_FOLLOW_YAW : 'vx' and 'vy'ÊÇËÙ¶È¿ØÖÆ£¬ 'wz'ÊÇÐý×ªËÙ¶È¿ØÖÆ
        CHASSIS_VECTOR_RAW : Ê¹ÓÃ'vx' 'vy' and 'wz'Ö±½ÓÏßÐÔ¼ÆËã³ö³µÂÖµÄµçÁ÷Öµ£¬µçÁ÷Öµ½«Ö±½Ó·¢ËÍµ½can ×ÜÏßÉÏ
    4.  ÔÚ"chassis_behaviour_control_set" º¯ÊýµÄ×îºó£¬Ìí¼Ó
        else if(chassis_behaviour_mode == CHASSIS_XXX_XXX)
        {
            chassis_xxx_xxx_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
        }
  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "chassis_behaviour.h"
#include "cmsis_os.h"
#include "chassis_task.h"
#include "arm_math.h"
#include <stdlib.h>

#include "gimbal_behaviour.h"

/**
  * @brief          when chassis behaviour mode is CHASSIS_ZERO_FORCE, the function is called
  *                 and chassis control mode is raw. The raw chassis control mode means set value
  *                 will be sent to CAN bus derectly, and the function will set all speed zero.
  * @param[out]     vx_can_set: vx speed value, it will be sent to CAN bus derectly.
  * @param[out]     vy_can_set: vy speed value, it will be sent to CAN bus derectly.
  * @param[out]     wz_can_set: wz rotate speed value, it will be sent to CAN bus derectly.
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌÎÞÁ¦µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇraw£¬¹Ê¶øÉè¶¨Öµ»áÖ±½Ó·¢ËÍµ½can×ÜÏßÉÏ¹Ê¶ø½«Éè¶¨Öµ¶¼ÉèÖÃÎª0
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      vy_set×óÓÒµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      wz_setÐý×ªµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */
static void chassis_zero_force_control(fp32 *vx_can_set, fp32 *vy_can_set, fp32 *wz_can_set, chassis_move_t *chassis_move_rc_to_vector);


/**
  * @brief          when chassis behaviour mode is CHASSIS_NO_MOVE, chassis control mode is speed control mode.
  *                 chassis does not follow gimbal, and the function will set all speed zero to make chassis no move
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: wz rotate speed value, positive value means counterclockwise , negative value means clockwise.
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ²»ÒÆ¶¯µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ²»¸úËæ½Ç¶È£¬
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_setÐý×ªµÄËÙ¶È£¬Ðý×ªËÙ¶ÈÊÇ¿ØÖÆµ×ÅÌµÄµ×ÅÌ½ÇËÙ¶È
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */
static void chassis_no_move_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector);

/**
  * @brief          when chassis behaviour mode is CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW, chassis control mode is speed control mode.
  *                 chassis will follow gimbal, chassis rotation speed is calculated from the angle difference.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     angle_set: control angle difference between chassis and gimbal
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¸úËæÔÆÌ¨µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ¸úËæÔÆÌ¨½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶È»á¸ù¾Ý½Ç¶È²î¼ÆËãµ×ÅÌÐý×ªµÄ½ÇËÙ¶È
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      angle_setµ×ÅÌÓëÔÆÌ¨¿ØÖÆµ½µÄÏà¶Ô½Ç¶È
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */
static void chassis_infantry_follow_gimbal_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set, chassis_move_t *chassis_move_rc_to_vector);

/**
  * @brief          when chassis behaviour mode is CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW, chassis control mode is speed control mode.
  *                 chassis will follow chassis yaw, chassis rotation speed is calculated from the angle difference between set angle and chassis yaw.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     angle_set: control angle[-PI, PI]
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¸úËæµ×ÅÌyawµÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ¸úËæµ×ÅÌ½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶È»á¸ù¾Ý½Ç¶È²î¼ÆËãµ×ÅÌÐý×ªµÄ½ÇËÙ¶È
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      angle_setµ×ÅÌÉèÖÃµÄyaw£¬·¶Î§ -PIµ½PI
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */
static void chassis_engineer_follow_chassis_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set, chassis_move_t *chassis_move_rc_to_vector);

/**
  * @brief          when chassis behaviour mode is CHASSIS_NO_FOLLOW_YAW, chassis control mode is speed control mode.
  *                 chassis will no follow angle, chassis rotation speed is set by wz_set.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: rotation speed,positive value means counterclockwise , negative value means clockwise
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ²»¸úËæ½Ç¶ÈµÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ²»¸úËæ½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶ÈÓÉ²ÎÊýÖ±½ÓÉè¶¨
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_setµ×ÅÌÉèÖÃµÄÐý×ªËÙ¶È,ÕýÖµ ÄæÊ±ÕëÐý×ª£¬¸ºÖµ Ë³Ê±ÕëÐý×ª
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */
static void chassis_no_follow_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector);



/**
  * @brief          when chassis behaviour mode is CHASSIS_OPEN, chassis control mode is raw control mode.
  *                 set value will be sent to can bus.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: rotation speed,positive value means counterclockwise , negative value means clockwise
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¿ª»·µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇrawÔ­Éú×´Ì¬£¬¹Ê¶øÉè¶¨Öµ»áÖ±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È£¬ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_set Ðý×ªËÙ¶È£¬ ÕýÖµ ÄæÊ±ÕëÐý×ª£¬¸ºÖµ Ë³Ê±ÕëÐý×ª
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         none
  */

static void chassis_open_set_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector);


//Ð¡ÍÓÂÝÒÆÖ²
static void chassis_little_gyro_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector);


//highlight, the variable chassis behaviour mode 
//ÁôÒâ£¬Õâ¸öµ×ÅÌÐÐÎªÄ£Ê½±äÁ¿
chassis_behaviour_e chassis_behaviour_mode = CHASSIS_ZERO_FORCE;


/**
  * @brief          logical judgement to assign "chassis_behaviour_mode" variable to which mode
  * @param[in]      chassis_move_mode: chassis data
  * @retval         none
  */
/**
  * @brief          Í¨¹ýÂß¼­ÅÐ¶Ï£¬¸³Öµ"chassis_behaviour_mode"³ÉÄÄÖÖÄ£Ê½
  * @param[in]      chassis_move_mode: µ×ÅÌÊý¾Ý
  * @retval         none
  */
void chassis_behaviour_mode_set(chassis_move_t *chassis_move_mode)
{
    if (chassis_move_mode == NULL)
    {
        return;
    }


    //remote control  set chassis behaviour mode
    //Ò£¿ØÆ÷ÉèÖÃÄ£Ê½
    if (switch_is_mid(chassis_move_mode->chassis_RC->rc.s[CHASSIS_MODE_CHANNEL]))
    {
        //can change to CHASSIS_ZERO_FORCE,CHASSIS_NO_MOVE,CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW,
        //CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW,CHASSIS_NO_FOLLOW_YAW,CHASSIS_OPEN
        chassis_behaviour_mode = CHASSIS_ZERO_FORCE; //µ×ÅÌÎÞÁ¦
    }
    else if (switch_is_down(chassis_move_mode->chassis_RC->rc.s[CHASSIS_MODE_CHANNEL]))
    {
        chassis_behaviour_mode = CHASSIS_LITTLE_GRYO; //Ð¡ÍÓÂÝ
    }
    else if (switch_is_up(chassis_move_mode->chassis_RC->rc.s[CHASSIS_MODE_CHANNEL]))
    {
        chassis_behaviour_mode = CHASSIS_NO_FOLLOW_YAW; //µ×ÅÌ¸úËæÔÆÌ¨
    }

    
		//when gimbal in some mode, such as init mode, chassis must's move
    //µ±ÔÆÌ¨ÔÚÄ³Ð©Ä£Ê½ÏÂ£¬Ïñ³õÊ¼»¯£¬ µ×ÅÌ²»¶¯
    if (gimbal_cmd_to_chassis_stop())
    {
        chassis_behaviour_mode = CHASSIS_NO_MOVE;
    }


    //add your own logic to enter the new mode
    //Ìí¼Ó×Ô¼ºµÄÂß¼­ÅÐ¶Ï½øÈëÐÂÄ£Ê½


    //accord to beheviour mode, choose chassis control mode
    //¸ù¾ÝÐÐÎªÄ£Ê½Ñ¡ÔñÒ»¸öµ×ÅÌ¿ØÖÆÄ£Ê½
    if (chassis_behaviour_mode == CHASSIS_ZERO_FORCE)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_RAW; 
    }
    else if (chassis_behaviour_mode == CHASSIS_NO_MOVE)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_NO_FOLLOW_YAW; 
    }
    else if (chassis_behaviour_mode == CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_FOLLOW_GIMBAL_YAW; 
    }
    else if (chassis_behaviour_mode == CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_FOLLOW_CHASSIS_YAW;
    }
    else if (chassis_behaviour_mode == CHASSIS_NO_FOLLOW_YAW)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_NO_FOLLOW_YAW;
    }
    else if (chassis_behaviour_mode == CHASSIS_OPEN)
    {
        chassis_move_mode->chassis_mode = CHASSIS_VECTOR_RAW;
    }
		else if (chassis_behaviour_mode == CHASSIS_LITTLE_GRYO)
		{
				chassis_move_mode->chassis_mode = CHASSIS_VECTOR_NO_FOLLOW_YAW; 
		}
}


/**
  * @brief          set control set-point. three movement param, according to difference control mode,
  *                 will control corresponding movement.in the function, usually call different control function.
  * @param[out]     vx_set, usually controls vertical speed.
  * @param[out]     vy_set, usually controls horizotal speed.
  * @param[out]     wz_set, usually controls rotation speed.
  * @param[in]      chassis_move_rc_to_vector,  has all data of chassis
  * @retval         none
  */
/**
  * @brief          ÉèÖÃ¿ØÖÆÁ¿.¸ù¾Ý²»Í¬µ×ÅÌ¿ØÖÆÄ£Ê½£¬Èý¸ö²ÎÊý»á¿ØÖÆ²»Í¬ÔË¶¯.ÔÚÕâ¸öº¯ÊýÀïÃæ£¬»áµ÷ÓÃ²»Í¬µÄ¿ØÖÆº¯Êý.
  * @param[out]     vx_set, Í¨³£¿ØÖÆ×ÝÏòÒÆ¶¯.
  * @param[out]     vy_set, Í¨³£¿ØÖÆºáÏòÒÆ¶¯.
  * @param[out]     wz_set, Í¨³£¿ØÖÆÐý×ªÔË¶¯.
  * @param[in]      chassis_move_rc_to_vector,  °üÀ¨µ×ÅÌËùÓÐÐÅÏ¢.
  * @retval         none
  */

void chassis_behaviour_control_set(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set, chassis_move_t *chassis_move_rc_to_vector)
{

    if (vx_set == NULL || vy_set == NULL || angle_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }

    if (chassis_behaviour_mode == CHASSIS_ZERO_FORCE)
    {
        chassis_zero_force_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
    else if (chassis_behaviour_mode == CHASSIS_NO_MOVE)
    {
        chassis_no_move_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
    else if (chassis_behaviour_mode == CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW)
    {
        chassis_infantry_follow_gimbal_yaw_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
    else if (chassis_behaviour_mode == CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW)
    {
        chassis_engineer_follow_chassis_yaw_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
    else if (chassis_behaviour_mode == CHASSIS_NO_FOLLOW_YAW)
    {
        chassis_no_follow_yaw_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
    else if (chassis_behaviour_mode == CHASSIS_OPEN)
    {
        chassis_open_set_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
		    else if (chassis_behaviour_mode == CHASSIS_LITTLE_GRYO)
    {
        chassis_little_gyro_control(vx_set, vy_set, angle_set, chassis_move_rc_to_vector);
    }
		
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_ZERO_FORCE, the function is called
  *                 and chassis control mode is raw. The raw chassis chontrol mode means set value
  *                 will be sent to CAN bus derectly, and the function will set all speed zero.
  * @param[out]     vx_can_set: vx speed value, it will be sent to CAN bus derectly.
  * @param[out]     vy_can_set: vy speed value, it will be sent to CAN bus derectly.
  * @param[out]     wz_can_set: wz rotate speed value, it will be sent to CAN bus derectly.
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌÎÞÁ¦µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇraw£¬¹Ê¶øÉè¶¨Öµ»áÖ±½Ó·¢ËÍµ½can×ÜÏßÉÏ¹Ê¶ø½«Éè¶¨Öµ¶¼ÉèÖÃÎª0
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      vy_set×óÓÒµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      wz_setÐý×ªµÄËÙ¶È Éè¶¨Öµ½«Ö±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */

static void chassis_zero_force_control(fp32 *vx_can_set, fp32 *vy_can_set, fp32 *wz_can_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_can_set == NULL || vy_can_set == NULL || wz_can_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }
    *vx_can_set = 0.0f;
    *vy_can_set = 0.0f;
    *wz_can_set = 0.0f;
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_NO_MOVE, chassis control mode is speed control mode.
  *                 chassis does not follow gimbal, and the function will set all speed zero to make chassis no move
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: wz rotate speed value, positive value means counterclockwise , negative value means clockwise.
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ²»ÒÆ¶¯µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ²»¸úËæ½Ç¶È£¬
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_setÐý×ªµÄËÙ¶È£¬Ðý×ªËÙ¶ÈÊÇ¿ØÖÆµ×ÅÌµÄµ×ÅÌ½ÇËÙ¶È
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */

static void chassis_no_move_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || wz_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }
    *vx_set = 0.0f;
    *vy_set = 0.0f;
    *wz_set = 0.0f;
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW, chassis control mode is speed control mode.
  *                 chassis will follow gimbal, chassis rotation speed is calculated from the angle difference.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     angle_set: control angle difference between chassis and gimbal
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¸úËæÔÆÌ¨µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ¸úËæÔÆÌ¨½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶È»á¸ù¾Ý½Ç¶È²î¼ÆËãµ×ÅÌÐý×ªµÄ½ÇËÙ¶È
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      angle_setµ×ÅÌÓëÔÆÌ¨¿ØÖÆµ½µÄÏà¶Ô½Ç¶È
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */

static void chassis_infantry_follow_gimbal_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || angle_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }

    //channel value and keyboard value change to speed set-point, in general
    //Ò£¿ØÆ÷µÄÍ¨µÀÖµÒÔ¼°¼üÅÌ°´¼ü µÃ³ö Ò»°ãÇé¿öÏÂµÄËÙ¶ÈÉè¶¨Öµ
    chassis_rc_to_control_vector(vx_set, vy_set, chassis_move_rc_to_vector);

    //swing angle is generated by sin function, swing_time is the input time of sin
    //Ò¡°Ú½Ç¶ÈÊÇÀûÓÃsinº¯ÊýÉú³É£¬swing_time ÊÇsinº¯ÊýµÄÊäÈëÖµ
    static fp32 swing_time = 0.0f;
    
    static fp32 swing_angle = 0.0f;
    //max_angle is the max angle that chassis will ratate
    //max_angle ÊÇsinº¯ÊýµÄ·ùÖµ
    static fp32 max_angle = SWING_NO_MOVE_ANGLE;
    //swing_time  plus the add_time in one control cycle
    //swing_time ÔÚÒ»¸ö¿ØÖÆÖÜÆÚÄÚ£¬¼ÓÉÏ add_time
    static fp32 const add_time = PI * 0.5f * configTICK_RATE_HZ / CHASSIS_CONTROL_TIME_MS;
    
    static uint8_t swing_flag = 0;

    //judge if swing
    //ÅÐ¶ÏÊÇ·ñÒªÒ¡°Ú
    if (chassis_move_rc_to_vector->chassis_RC->key.v & SWING_KEY)
    {
        if (swing_flag == 0)
        {
            swing_flag = 1;
            swing_time = 0.0f;
        }
    }
    else
    {
        swing_flag = 0;
    }

    //judge if keyboard is controlling the chassis, if yes, reduce the max_angle
    //ÅÐ¶Ï¼üÅÌÊäÈëÊÇ²»ÊÇÔÚ¿ØÖÆµ×ÅÌÔË¶¯£¬µ×ÅÌÔÚÔË¶¯¼õÐ¡Ò¡°Ú½Ç¶È
    if (chassis_move_rc_to_vector->chassis_RC->key.v & CHASSIS_FRONT_KEY || chassis_move_rc_to_vector->chassis_RC->key.v & CHASSIS_BACK_KEY ||
        chassis_move_rc_to_vector->chassis_RC->key.v & CHASSIS_LEFT_KEY || chassis_move_rc_to_vector->chassis_RC->key.v & CHASSIS_RIGHT_KEY)
    {
        max_angle = SWING_MOVE_ANGLE;
    }
    else
    {
        max_angle = SWING_NO_MOVE_ANGLE;
    }
    
    if (swing_flag)
    {
        swing_angle = max_angle * arm_sin_f32(swing_time);
        swing_time += add_time;
    }
    else
    {
        swing_angle = 0.0f;
    }
    //swing_time  range [0, 2*PI]
    //sinº¯Êý²»³¬¹ý2pi
    if (swing_time > 2 * PI)
    {
        swing_time -= 2 * PI;
    }


    *angle_set = swing_angle;
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW, chassis control mode is speed control mode.
  *                 chassis will follow chassis yaw, chassis rotation speed is calculated from the angle difference between set angle and chassis yaw.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     angle_set: control angle[-PI, PI]
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¸úËæµ×ÅÌyawµÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ¸úËæµ×ÅÌ½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶È»á¸ù¾Ý½Ç¶È²î¼ÆËãµ×ÅÌÐý×ªµÄ½ÇËÙ¶È
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      angle_setµ×ÅÌÉèÖÃµÄyaw£¬·¶Î§ -PIµ½PI
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */

static void chassis_engineer_follow_chassis_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || angle_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }

    chassis_rc_to_control_vector(vx_set, vy_set, chassis_move_rc_to_vector);

    *angle_set = rad_format(chassis_move_rc_to_vector->chassis_yaw_set - CHASSIS_ANGLE_Z_RC_SEN * chassis_move_rc_to_vector->chassis_RC->rc.ch[CHASSIS_WZ_CHANNEL]);
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_NO_FOLLOW_YAW, chassis control mode is speed control mode.
  *                 chassis will no follow angle, chassis rotation speed is set by wz_set.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: rotation speed,positive value means counterclockwise , negative value means clockwise
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ²»¸úËæ½Ç¶ÈµÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇ²»¸úËæ½Ç¶È£¬µ×ÅÌÐý×ªËÙ¶ÈÓÉ²ÎÊýÖ±½ÓÉè¶¨
  * @author         RM
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È,ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_setµ×ÅÌÉèÖÃµÄÐý×ªËÙ¶È,ÕýÖµ ÄæÊ±ÕëÐý×ª£¬¸ºÖµ Ë³Ê±ÕëÐý×ª
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         ·µ»Ø¿Õ
  */

static void chassis_no_follow_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || wz_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }

    chassis_rc_to_control_vector(vx_set, vy_set, chassis_move_rc_to_vector);
    *wz_set = -CHASSIS_WZ_RC_SEN * chassis_move_rc_to_vector->chassis_RC->rc.ch[CHASSIS_WZ_CHANNEL];
}

/**
  * @brief          when chassis behaviour mode is CHASSIS_OPEN, chassis control mode is raw control mode.
  *                 set value will be sent to can bus.
  * @param[out]     vx_set: vx speed value, positive value means forward speed, negative value means backward speed,
  * @param[out]     vy_set: vy speed value, positive value means left speed, negative value means right speed.
  * @param[out]     wz_set: rotation speed,positive value means counterclockwise , negative value means clockwise
  * @param[in]      chassis_move_rc_to_vector: chassis data
  * @retval         none
  */
/**
  * @brief          µ×ÅÌ¿ª»·µÄÐÐÎª×´Ì¬»úÏÂ£¬µ×ÅÌÄ£Ê½ÊÇrawÔ­Éú×´Ì¬£¬¹Ê¶øÉè¶¨Öµ»áÖ±½Ó·¢ËÍµ½can×ÜÏßÉÏ
  * @param[in]      vx_setÇ°½øµÄËÙ¶È,ÕýÖµ Ç°½øËÙ¶È£¬ ¸ºÖµ ºóÍËËÙ¶È
  * @param[in]      vy_set×óÓÒµÄËÙ¶È£¬ÕýÖµ ×óÒÆËÙ¶È£¬ ¸ºÖµ ÓÒÒÆËÙ¶È
  * @param[in]      wz_set Ðý×ªËÙ¶È£¬ ÕýÖµ ÄæÊ±ÕëÐý×ª£¬¸ºÖµ Ë³Ê±ÕëÐý×ª
  * @param[in]      chassis_move_rc_to_vectorµ×ÅÌÊý¾Ý
  * @retval         none
  */

static void chassis_open_set_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || wz_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }

    *vx_set = chassis_move_rc_to_vector->chassis_RC->rc.ch[CHASSIS_X_CHANNEL] * CHASSIS_OPEN_RC_SCALE;
    *vy_set = -chassis_move_rc_to_vector->chassis_RC->rc.ch[CHASSIS_Y_CHANNEL] * CHASSIS_OPEN_RC_SCALE;
    *wz_set = -chassis_move_rc_to_vector->chassis_RC->rc.ch[CHASSIS_WZ_CHANNEL] * CHASSIS_OPEN_RC_SCALE;
    return;
}

//Ð¡ÍÓÂÝÒÆÖ²º¯Êý
static void chassis_little_gyro_control(float *vx_set, float *vy_set, float *wz_set, chassis_move_t *chassis_move_rc_to_vector)
{
    if (vx_set == NULL || vy_set == NULL || wz_set == NULL || chassis_move_rc_to_vector == NULL)
    {
        return;
    }
		
		/*¾ø¶ÔÖµÏÞÖÆº¯Êý×**/
		#define TOOL_ABS_LIMIT(a, max) 
		/* µ×ÅÌÖá¾à(mm) */
		#define CONFIG_CHASSIS_WHEELBASE      370
		/* µ×ÅÌÂÖ¾à(mm) */
		#define CONFIG_CHASSIS_WHEELTRACK     353
		/* ÔÆÌ¨Æ«ÒÆ(mm) */
		#define CONFIG_CHASSIS_GIMBAL_OFFSET  0
		/* µ×ÅÌÂÖ×ÓÖÜ³¤(mm) */
		#define CONFIG_CHASSIS_PERIMETER      478
		/* µ×ÅÌµç»ú¼õËÙ±È(3508) */
		#define CONFIG_CHASSIS_DECELE_RATIO   (1.0f/19.0f)
		/* ½Ç¶È×ª»¡¶ÈÏµÊý */
		#define TOOL_RADIAN_COEF      57.3f
		/* µ×ÅÌÒÆ¶¯×î´óËÙ¶È£¬µ¥Î»ÊÇºÁÃ×Ã¿Ãë */
		#define CONFIG_CHASSIS_MAX_VX_SPEED   2900
		#define CONFIG_CHASSIS_MAX_VY_SPEED   2900
		/* µ×ÅÌÐý×ª×î´óËÙ¶È£¬µ¥Î»ÊÇ¶ÈÃ¿Ãë */
		#define CONFIG_CHASSIS_MAX_VR_SPEED   100
		/* µ¥¸öµç»úËÙ¶È¼«ÏÞ£¬µ¥Î»ÊÇ·ÖÖÓÃ¿×ª, 8347rpm = 3500mm/s */
		#define CONFIG_CHASSIS_MAX_WHEEL_RPM  8500
		
		
		
		static float rotateRatioF = ((CONFIG_CHASSIS_WHEELBASE + CONFIG_CHASSIS_WHEELTRACK)/2.0f - CONFIG_CHASSIS_GIMBAL_OFFSET)/TOOL_RADIAN_COEF;
		static float rotateRatioB = ((CONFIG_CHASSIS_WHEELBASE + CONFIG_CHASSIS_WHEELTRACK)/2.0f + CONFIG_CHASSIS_GIMBAL_OFFSET)/TOOL_RADIAN_COEF;
		static float wheelRPMRatio = 60.0f/(CONFIG_CHASSIS_PERIMETER * CONFIG_CHASSIS_DECELE_RATIO);
		int16_t wheelRPM[4];
		float max = 0;

		TOOL_ABS_LIMIT(vx_set, CONFIG_CHASSIS_MAX_VX_SPEED);  //mm/s
		TOOL_ABS_LIMIT(vy_set, CONFIG_CHASSIS_MAX_VY_SPEED);  //mm/s
		TOOL_ABS_LIMIT(wz_set, CONFIG_CHASSIS_MAX_VR_SPEED);  //deg/s

		wheelRPM[0] = (+*vx_set - *vy_set + *wz_set * rotateRatioF) * wheelRPMRatio;
  	wheelRPM[1] = (+*vx_set + *vy_set + *wz_set * rotateRatioF) * wheelRPMRatio;
  	wheelRPM[2] = (-*vx_set + *vy_set + *wz_set * rotateRatioB) * wheelRPMRatio;
  	wheelRPM[3] = (-*vx_set - *vy_set + *wz_set * rotateRatioB) * wheelRPMRatio;

  	//find max item
  	for (size_t i = 0; i < 4; i++) {
  		if (abs(wheelRPM[i]) > max) {
  			max = abs(wheelRPM[i]);
  		}
  	}
  	//equal proportion
  	if (max > CONFIG_CHASSIS_MAX_WHEEL_RPM) {
  		float rate = CONFIG_CHASSIS_MAX_WHEEL_RPM / max;
  		for (size_t i = 0; i < 4; i++) {
  			wheelRPM[i] *= rate;
  		}
  	}
  	memcpy(chassis_move_rc_to_vector, wheelRPM, 4 * sizeof(int16_t));

    return;
}
