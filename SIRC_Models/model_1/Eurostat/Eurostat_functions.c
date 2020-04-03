#include "../header.h"
#include "../Eurostat_agent_header.h"
#include "../my_library_header.h"
#include "Eurostat_aux_headers.h"

/***************** TEMPLATE ****************/
/** \fn Eurostat_TEMPLATE()
 * \brief Function to
 * \brief Message input: None
 * \brief Message output: 
 * \brief UNITTEST: TODO
 */
/*
int Eurostat_TEMPLATE()
{
  	//Message input:

	//Message output:

    #ifdef _DEBUG_MODE    
    if (PRINT_BANK_MORTGAGE_INFO)
    {
        printf("\n\n Bank_ ID: %d", ID);
    }      
    #endif
 
 return 0;   
}
*/
/***************** END OF TEMPLATE ****************/

/** \fn Eurostat_init()
 * \brief Function to 
 * \brief - Message input:  None
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
/*
int Eurostat_init()
{
	return 0;   
}
*/

/** \fn Eurostat_read_info()
 * \brief Function to 
 * \brief - Message input: status_info_message
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Eurostat_read_info()
{
	int i,temp_status;
		
	COUNT_SUM=0;

	for(i=0; i<COUNT.size; i++)
		COUNT.array[i]=0;
	
	START_LOCAL_STATUS_INFO_MESSAGE_LOOP

		temp_status=local_status_info_message->status;
		COUNT.array[temp_status]++;
		COUNT_SUM++;

		#ifdef _DEBUG_MODE    
		if (PRINT_STATUS_INFO_EUROSTAT)
		{
			printf("\n[Read] id %3d status %d", temp_id, temp_status);
		}
		#endif

	FINISH_LOCAL_STATUS_INFO_MESSAGE_LOOP

	COUNT_STATUS_0=COUNT.array[0];
	COUNT_STATUS_1=COUNT.array[1];
	COUNT_STATUS_2=COUNT.array[2];
	COUNT_STATUS_3=COUNT.array[3];

	if(COUNT_SUM>0)
	{
		FREQ_STATUS_0=((double)COUNT.array[0])/COUNT_SUM;
		FREQ_STATUS_1=((double)COUNT.array[1])/COUNT_SUM;
		FREQ_STATUS_2=((double)COUNT.array[2])/COUNT_SUM;
		FREQ_STATUS_3=((double)COUNT.array[3])/COUNT_SUM;
	}

	#ifdef _DEBUG_MODE    
	if (PRINT_STATUS_INFO_EUROSTAT)
	{
		printf("\n[COUNT_STATUS] %3d %3d %3d %3d", COUNT_STATUS_0, COUNT_STATUS_1, COUNT_STATUS_2, COUNT_STATUS_3);
		printf("\n[FREQ_STATUS] %.2f %.2f %.2f %.2f\n", FREQ_STATUS_0, FREQ_STATUS_1, FREQ_STATUS_2, FREQ_STATUS_3);
	}
	#endif

	return 0;   
}
