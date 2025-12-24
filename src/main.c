#include "Screen.h" 

// ---------------------------------------------------------------------------
// MAIN (Test Loop)
// ---------------------------------------------------------------------------
int main(void){
    int i;
    
    // Initialize
    ScreenInit();
    
    // Clear any random noise
    ScreenClear();

		// Reset Cursor to top left
		ScreenWrite(0, 0x80);
		ScreenWrite(0, 0x40);
        
    // Loop forever drawing a pattern
    while(1){
        // Draw Diagonal Line Pattern
        for(i=0; i<84; i++){
            // Creates a shifting bit pattern
            ScreenWrite(1, (1 << (i % 8))); 
        }
        
        // Wait so you can see if the screen resets or flickers
        Delay(400000);
        
        // Invert screen command (Test if commands are working)
        ScreenWrite(0, 0x0D); // Inverse Video
        Delay(400000);
        ScreenWrite(0, 0x0C); // Normal Video
    }
}