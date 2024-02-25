/* Event base class */
typedef struct {
    Signal sig; /* event signal */
    /* event parameters added in subclasses of Event */
} Event;

/*---------------------------------------------------------------------------*/
/* Actvie Object facilities... */

typedef struct Active Active; /* forward declaration */
typedef void (*DispatchHandler)(Active * const me, Event const * const e);

/* Active Object base class */
struct Active 
{
    INT8U thread;     /* private thread (the unique uC/OS-II task priority) */
    OS_EVENT *queue;  /* private message queue */

    DispatchHandler dispatch; /* pointer to the dispatch() function */

    /* active object data added in subclasses of Active */
};