;
ADC0_BASE_ADDR 		EQU 	0x40038000 
ADC0_PSSI_ADDR 		EQU 	0x40038028
ADC0_RIS_ADDR 		EQU 	0x40038004
ADC0_SSFIFO3_ADDR 	EQU 	0x400380A8
ADC0_ISC_ADDR 		EQU 	0x4003800C
	
;LABEL		DIRECTIVE	VALUE			COMMENT
            AREA 		ReadPoten, READONLY, CODE
            THUMB
			EXPORT 		ReadPot
				
;ReadPot Function	
;***************************************************************
;LABEL		DIRECTIVE	VALUE					COMMENT	
ReadPot		PROC	
			PUSH		{R4,R5,R6,LR}
			
			MOV			R5, #0x08
			LDR			R4, =ADC0_PSSI_ADDR
			STR			R5, [R4]
			LDR			R4, =ADC0_RIS_ADDR
loop		LDR			R5, [R4]
			CMP			R5, #0x00
			BNE			continue;
			B			loop
continue	LDR			R4, =ADC0_SSFIFO3_ADDR
			LDR			R5, [R4]
			MOV			R6, #0xFFF
			AND			R6, R5, R6
			
			LDR			R4, =ADC0_ISC_ADDR
			MOV			R5, #0x08
			STR			R5, [R4]
			MOV			R0, R6
			
			POP			{R4,R5,R6,LR}
			BX			LR
			ENDP
			
			
			
			END
	