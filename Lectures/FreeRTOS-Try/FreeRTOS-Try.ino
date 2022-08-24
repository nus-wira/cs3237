#include <Arduino_FreeRTOS.h>
// Each task is a separate function. An example of 2 tasks:
void TaskA( void *pvParameters );
void TaskB( void *pvParameters );

void setup() {

  Serial.begin(9600);
  
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskA   //function that executes the task
    ,  (const portCHAR *)"Task A"   // For human only
    ,  128  // Stack size
    ,  NULL // Parameter passed to the task
    ,  2    // priority
    ,  NULL );  //Task handler for future operation

  xTaskCreate( TaskB,  (const portCHAR *) "TaskB"
    ,  128 ,  NULL,  1,  NULL );

  // The RTOS scheduler is automatically started when 
  // setup() finishes
}

void loop()
{
   //Empty. The tasks contains all processing
}

void TaskA(void *pvParameters)  // This is a task.
{
    for (;;){ // A Task shall never return or exit.
        Serial.println("A");
        vTaskDelay( 100 / portTICK_PERIOD_MS ); //delay(100)
    }
}

void TaskB(void *pvParameters)  // Another task
{
  
  for (;;)  {
      Serial.println("B");
      vTaskDelay( 100 / portTICK_PERIOD_MS );
  }
}

//vTaskDelay( 100 / portTICK_PERIOD_MS );
