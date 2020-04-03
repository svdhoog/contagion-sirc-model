#include "../header.h"
#include "../Human_agent_header.h"
#include "../my_library_header.h"

#define ITER iteration_loop

/***************** TEMPLATE ****************/
/** \fn Human_TEMPLATE()
 * \brief Function to
 * \brief Message input: None
 * \brief Message output: 
 * \brief UNITTEST: TODO
 */
/*
int Human_TEMPLATE()
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


/** \fn Human_send_info()
 * \brief Function to 
 * \brief - Message input: status_info_message
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_send_info()
{

	#ifdef _DEBUG_MODE    
	if (PRINT_INFO)
	{
		printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
		printf("\n[Send] ID %d status %d", ID, STATUS);
	}
	#endif
	
	add_status_info_message(ID, STATUS);
	
	return 0;   
}

/** \fn Human_read_info()
 * \brief Function to 
 * \brief - Message input: None
 * \brief - Message output: status_info_message
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_read_info()
{
	int temp_id, temp_status;
	
	START_STATUS_INFO_MESSAGE_LOOP

		temp_id = status_info_message->id;
		temp_status = status_info_message->status;

		#ifdef _DEBUG_MODE    
		if (PRINT_INFO)
		{
			printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
			printf("\n[Read] id %d status %d", temp_id, temp_status);
		}
		#endif

	FINISH_STATUS_INFO_MESSAGE_LOOP

	return 0;   
}
