#include "./BSP/ic/ic.h"
#include "./BSP/LED/led.h"

/*********************************������ͨ�ö�ʱ�����벶��ʵ�����*************************************/

TIM_HandleTypeDef g_timx_cap_chy_handle;      /* ��ʱ��x��� */

/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y ���벶�� ��ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_cap_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_IC_InitTypeDef timx_ic_cap_chy = {0};

    g_timx_cap_chy_handle.Instance = GTIM_TIMX_CAP;                     /* ��ʱ��5 */
    g_timx_cap_chy_handle.Init.Prescaler = psc;                         /* ��ʱ����Ƶ */
    g_timx_cap_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_cap_chy_handle.Init.Period = arr;                            /* �Զ���װ��ֵ */
    HAL_TIM_IC_Init(&g_timx_cap_chy_handle);

    timx_ic_cap_chy.ICPolarity = TIM_ICPOLARITY_RISING;                 /* �����ز��� */
    timx_ic_cap_chy.ICSelection = TIM_ICSELECTION_DIRECTTI;             /* ӳ�䵽TI1�� */
    timx_ic_cap_chy.ICPrescaler = TIM_ICPSC_DIV1;                       /* ���������Ƶ������Ƶ */
    timx_ic_cap_chy.ICFilter = 0;                                       /* ���������˲��������˲� */
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_chy_handle, &timx_ic_cap_chy, GTIM_TIMX_CAP_CHY);  /* ����TIM5ͨ��1 */

    __HAL_TIM_ENABLE_IT(&g_timx_cap_chy_handle, TIM_IT_UPDATE);         /* ʹ�ܸ����ж� */
    HAL_TIM_IC_Start_IT(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);     /* ��ʼ����TIM5��ͨ��1 */
}

/**
 * @brief       ͨ�ö�ʱ�����벶���ʼ���ӿ�
                HAL����õĽӿڣ��������ò�ͬ�����벶��
 * @param       htim:��ʱ�����
 * @note        �˺����ᱻHAL_TIM_IC_Init()����
 * @retval      ��
 */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)                    /*����ͨ������*/
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIMX_CAP_CHY_CLK_ENABLE();                     /* ʹ��TIMxʱ�� */
        GTIM_TIMX_CAP_CHY_GPIO_CLK_ENABLE();                /* ��������IO��ʱ�� */

        gpio_init_struct.Pin = GTIM_TIMX_CAP_CHY_GPIO_PIN;  /* ���벶���GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLDOWN;              /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;      /* ���� */
        HAL_GPIO_Init(GTIM_TIMX_CAP_CHY_GPIO_PORT, &gpio_init_struct);

        HAL_NVIC_SetPriority(GTIM_TIMX_CAP_IRQn, 1, 3);     /* ��ռ1�������ȼ�3 */
        HAL_NVIC_EnableIRQ(GTIM_TIMX_CAP_IRQn);             /* ����ITMx�ж� */
    }
}

/* ���벶��״̬(g_timxchy_cap_sta)
 * [7]  :0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
 * [6]  :0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
 * [5:0]:����ߵ�ƽ������Ĵ���,������63��,���������ֵ = 63*65536 + 65535 = 4194303
 *       ע��:Ϊ��ͨ��,����Ĭ��ARR��CCRy����16λ�Ĵ���,����32λ�Ķ�ʱ��(��:TIM5),Ҳֻ��16λʹ��
 *       ��1us�ļ���Ƶ��,����ʱ��Ϊ:4194303 us, Լ4.19��
 *
 *      (˵��һ�£�����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
 */
uint8_t g_timxchy_cap_sta = 0;    /* ���벶��״̬ */
uint16_t g_timxchy_cap_val = 0;   /* ���벶��ֵ */


/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_CAP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_chy_handle);  /* ��ʱ��HAL�⹲�ô����� */
}

/**
 * @brief       ��ʱ�����벶���жϴ���ص�����
 * @param       htim:��ʱ�����ָ��
 * @note        �ú�����HAL_TIM_IRQHandler�лᱻ����
 * @retval      ��
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)                /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)                   /* ����һ���½��� */
            {
                g_timxchy_cap_sta |= 0X80;                  /* ��ǳɹ�����һ�θߵ�ƽ���� */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);  /* ��ȡ��ǰ�Ĳ���ֵ */
                /* RESET : �������λ ��Ӳ������˵Ч���൱������Ϊ�����ز��� ��������һ�д������ע��*/
                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);                      /* һ��Ҫ�����ԭ�������� */
//                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING); /* ����TIM5ͨ��1�����ز��� */
            }
            else /* ��δ��ʼ,��һ�β��������� */
            {
                g_timxchy_cap_sta = 0;                              /* ��� */
                g_timxchy_cap_val = 0;
                g_timxchy_cap_sta |= 0X40;                          /* ��ǲ����������� */
                __HAL_TIM_SET_COUNTER(&g_timx_cap_chy_handle, 0);   /* ��ʱ��5���������� */
//                TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);   /* һ��Ҫ�����ԭ�������ã��� */
                TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_FALLING); /* ��ʱ��5ͨ��1����Ϊ�½��ز��� */
            }
        }
    }
}

/**
 * @brief       ��ʱ�������жϻص�����
 * @param        htim:��ʱ�����ָ��
 * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)
    {
        if ((g_timxchy_cap_sta & 0X80) == 0)            /* ��δ�ɹ����� */
        {
            if (g_timxchy_cap_sta & 0X40)               /* �Ѿ����񵽸ߵ�ƽ�� */
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* �ߵ�ƽ̫���� */
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY);                     /* һ��Ҫ�����ԭ�������� */
//                    TIM_SET_CAPTUREPOLARITY(&g_timx_cap_chy_handle, GTIM_TIMX_CAP_CHY, TIM_ICPOLARITY_RISING);/* ����TIM5ͨ��1�����ز��� */
                    g_timxchy_cap_sta |= 0X80;          /* ��ǳɹ�������һ�� */
                    g_timxchy_cap_val = 0XFFFF;
                }
                else      /* �ۼƶ�ʱ��������� */
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}
/**
 * @brief       ��ȡ�������µ�ʱ��
 * @param        ptitm:  ����ָ����и�ֵ
 * @note        ��λΪus ���4194303 us, Լ4.19��,
 * @retval      1����Ƭ����⵽�����İ������������º�̧�� 0 ��û�м�⵽���������İ�������
 */
uint8_t tim_cpt_key(uint32_t *ptitm)
{
    *ptitm = 0;                             /* ���� */
    if (!(g_timxchy_cap_sta & 0X80))       /* �ɹ�������һ�θߵ�ƽ */
    return 0;
    
    *ptitm = (g_timxchy_cap_sta & 0X3F)*65536 + g_timxchy_cap_val;/* ����ʱ�� ��λΪus ����ֵ��ָ�� */
    g_timxchy_cap_sta = 0;          /* ������һ�β���*/
    
    return 1;
}

