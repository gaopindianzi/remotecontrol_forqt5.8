#ifndef __JTHREAD_H__
#define __JTHREAD_H__

#define PT_WAIT_KO    0
#define PT_WAIT_OK    1
#define PT_TIMEOUT    2

typedef struct __jtctl
{
  unsigned int line;
  uint16_t     tick;
  uint16_t     curr;
  uint16_t     esc;
  unsigned char result;
} jt_ctl;

extern  uint16_t get_sys_tick16(void);

#define  __JT_SWITCH(jt)   switch((jt).line) { case 0:
#define  __JT_ENDCASE(jt)  }}
#define  __JT_DELAY(jt,ms)  (jt).tick = (jt).curr; \
                            (jt).line = __LINE__;  return ; case __LINE__:  \
						                if((jt).esc < (ms)) return ;
#define  __JT_SET_LINE(jt)  (jt).line = __LINE__; return ; case __LINE__:
						  
#define  __WAIT_UNTIL(jt,con)   __JT_SET_LINE(jt); if(!(con)) return ;



//-----------------------------------------------------------
#define  JT_BEGIN(jt)    { (jt).curr = get_sys_tick16(); (jt).esc = (jt).curr - (jt).tick; \
                             __JT_SWITCH(jt) 

#define  JT_END(jt)          default: (jt).line = 0; __JT_ENDCASE(jt)

#define  JT_DELAY_MS(jt,ms)   __JT_DELAY(jt,ms)

#define  JT_WAIT_UNTIL(jt,con)  __WAIT_UNTIL(jt,con)
	
#define  JT_DELAY_MS_OR_UNTIL(jt, condition, msmsmsms)	        \
  do {						\
		(jt).tick = get_sys_tick16();   \
    __JT_SET_LINE(jt);  \
		{   \
			char cod = (condition);   \
			char timot = ((jt).esc >= (msmsmsms));  \
      if(!cod && !timot) {				\
        return ;			\
      }						\
		  if(timot) {		\
			  (jt).result = PT_TIMEOUT;  \
		  } else if(cod) {  \
				(jt).result = PT_WAIT_OK;  \
			}  \
		}  \
  } while(0)
	
#define JT_GET_RESULT(jt)   ((jt).result)
	
	
#define  JT_SLEEP_TICK(jt)     __JT_SET_LINE(jt)
	
	
	





//----------------------------------------------------------









/** \hideinitializer */
typedef struct _jc_ctl
{
  void *   enter;
  uint16_t tick;
  uint16_t curr;
  uint16_t esc;
} jc_ctl;

#define JC_BEGIN(s)				\
  do { (s).curr = get_sys_tick16();   \
	 (s).esc = (s).curr - (s).tick;  \
    if((s).jc != 0) {				\
      goto *((s).jc);				 \
    }						\
  } while(0)

#define JC_CONCAT2(s1, s2) s1##s2
#define JC_CONCAT(s1, s2) JC_CONCAT2(s1, s2)
  
#define JC_WAIT_UNTIL(s,cond)				\
  do {					\
	(s).jc = &&JC_CONCAT(JC_LABEL, __LINE__); return ; JC_CONCAT(JC_LABEL, __LINE__):  \
	if(!(cond)) return ;   \
  } while(0)
  
#define JC_DELAY_MS(s,ms)				\
  do {	(s).tick = (s).curr;  \
	(s).jc = &&JC_CONCAT(JC_LABEL, __LINE__); return ; JC_CONCAT(JC_LABEL, __LINE__):  \
	if(!((s).esc > (ms))) return ;   \
  } while(0)

#define JC_END(s)




























#endif
