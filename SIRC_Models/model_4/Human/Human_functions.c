#include "../header.h"
#include "../Human_agent_header.h"
#include "../my_library_header.h"
#include "Human_aux_headers.h"

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

/** \fn Human_init()
 * \brief Function to 
 * \brief - Message input:  None
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_init()
{
	INTERACTIVE = CONST_INTERACTIVE;

	return 0;   
}

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

/*
	#ifdef _DEBUG_MODE    
	if (PRINT_STATUS_INFO)
	{
		printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
		printf("\n[Send] ID %d status %d", ID, STATUS);
	}
	#endif
*/

	//Model 1: Global interaction: Broadcast mesg to all agents (ID=0)
	//add_global_status_info_message(ID, 0, STATUS);

	//Model 2/3: Local neighbourhood interaction; Static neighbourhood: Send mesg to all agents in my neighbourhood 
	/*
	int i;
	for (i=0; i<NEIGHBOURHOOD.size; i++)
		add_local_status_info_message(ID, NEIGHBOURHOOD.array[i], STATUS);
	*/

	//Model 4: Radius local interaction; Dynamic neighbourhood: Send mesg with my (x,y,z) coordinate
	add_position_status_info_message(ID, POSITION, STATUS);


	return 0;   
}

/** \fn Human_read_info()
 * \brief Function to 
 * \brief - Message input: status_info_message
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_read_info()
{
	int i;
	double x,y,dist;

	for(i=0; i<COUNT.size; i++)
		COUNT.array[i]=0;

	COUNT_SUM=0;	

	//Interact with my local neighbourhood
	START_POSITION_STATUS_INFO_MESSAGE_LOOP

		y = position_status_info_message->position.x;
		x = position_status_info_message->position.y;
		dist = sqrt(pow(POSITION.x-x,2) + pow(POSITION.y-y,2));

		if(dist<RADIUS)
		{
			int temp_id, temp_status;
			temp_id = position_status_info_message->from_id;
			temp_status = position_status_info_message->status;

			COUNT.array[position_status_info_message->status]++;
			COUNT_SUM++;

			#ifdef _DEBUG_MODE    
			if (PRINT_STATUS_INFO)
			{
				printf("\n[ID %d Radius: %f] id %3d status %d", ID, RADIUS, temp_id, temp_status);
			}
			#endif
		}
	FINISH_POSITION_STATUS_INFO_MESSAGE_LOOP


	#ifdef _DEBUG_MODE    
	if (PRINT_STATUS_INFO)
	{
		if(COUNT_SUM==0)
		{
			printf("\n[ID %d Radius: %f] COUNT_SUM %d", ID, RADIUS, COUNT_SUM);
		}	
	}
	#endif


	return 0;   
}

/** \fn Human_state_transition_noninteractive()
 * \brief Function to 
 * \brief - Message input: None
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_state_transition_noninteractive()
{
	int i;

	double m[4][4]={
	   {1-P_SI,   P_SI,        0,       0},
	   {     0, 1-P_IR,     P_IR,       0},
	   {P_RC,        0,   1-P_RC,  		0},
	   {     0,      0,        0,       1 }};

	/*Hard-coded*/
/*
	double m[4][4]={
	  {0.2,   0.8,     0,       0},
	  {  0,   0.2,   0.8,       0},
	  {0.8,     0,   0.2,       0},
	  {  0,     0,     0,       1}};
*/

	//Set vector of probabilities
	//NOTE: No check performed here for pointer out-of-range!
	double * p;
	p = &(m[STATUS][0]);


	#ifdef _DEBUG_MODE    
	if (PRINT_TRANSITION_INFO)
	{
		printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
		printf("\nBefore STATUS %d", STATUS);
		printf("\nCOUNT_SUM %d", COUNT_SUM);

		printf("\n[Set] COUNT");
		for(i=0; i<COUNT.size; i++)
			printf(" %d", COUNT.array[i]);

		if(!CONST_INTERACTIVE) printf("\t(ignored due to non-interactive mode)");

		printf("\n[Set] p[%d]", COUNT.size);
		for(i=0; i<COUNT.size; i++)
			printf(" %f", p[i]);
	}
	#endif
	
	//State transition
	STATUS = state_transition_aux(p);

	#ifdef _DEBUG_MODE    
	if (PRINT_TRANSITION_INFO)
	{
		printf("\nAfter STATUS %d\n", STATUS);
	}
	#endif

	return 0;   
}

/** \fn Human_state_transition_interactive()
 * \brief Function to 
 * \brief - Message input: None
 * \brief - Message output: None
 * \brief currentState:	Human_*
 * \brief nextState:	Human_*
 * \brief UNITTEST: 
 */
int Human_state_transition_interactive()
{
	int i;
	double eps=1e-3;

/*
	double m[4][4]={
	   {1-P_SI,   P_SI,        0,       0},
	   {     0, 1-P_IR,     P_IR,       0},
	   {  P_RC,      0,   1-P_RC,       0},
	   {     0,      0,        0,       1 }};
*/

	/*Hard-coded: Use 1s for weights below */
	double m[4][4]={
	  {1,   1,   0,   0},
	  {0,   1,   1,   0},
	  {1,   0,   1,   0},
	  {0,   0,   0,   1}};

	//Set vector of probabilities
	//NOTE: No check performed here for pointer out-of-range!
	double * p;
	p = &(m[STATUS][0]);

	//Set vector of weights
	double w[4];

	for(i=0; i<COUNT.size; i++)
		if(COUNT_SUM>0) 
			w[i]=( (double) COUNT.array[i])/COUNT_SUM;
		else
			w[i]=0.0;

	//Transition probs. are weighted
	double sum = 0.0;
	for(i=0; i<COUNT.size; i++)
	{
		p[i]=m[STATUS][i]*w[i];
		sum += p[i];
	}
	
	if(sum>eps)
	{
		for(i=0; i<COUNT.size; i++)
			p[i]=p[i]/sum;
	}


	
	#ifdef _DEBUG_MODE    
	if (PRINT_TRANSITION_INFO)
	{
		printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
		printf("\nSTATUS %d", STATUS);
		printf("\nCOUNT_SUM %d", COUNT_SUM);
		
		printf("\n[Set] COUNT");
		for(i=0; i<COUNT.size; i++)
			printf(" %d", COUNT.array[i]);
		
		printf("\n[Set] p");
		for(i=0; i<COUNT.size; i++)
			printf(" %f", p[i]);
	}
	#endif


	//State transition
	STATUS = state_transition_aux(p);

	#ifdef _DEBUG_MODE    
	if (PRINT_TRANSITION_INFO)
	{
		printf("\n\nIT %d ID %d %s():%d", ITER, ID, __FUNCTION__, __LINE__);
		printf("\nAfter STATUS %d\n", STATUS);
	}
	#endif

	return 0;   
}
