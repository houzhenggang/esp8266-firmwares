<?php
// START_SYSEX
sendchar( 0xF0 );
// DEBUG_PIN_VALUE
sendchar( 0x39 );
// pin 1
sendchar( 0x01 );
// 0
sendchar( 0x00 );
// val
sendchar( 0x01 );
// 0
sendchar( 0x00 );
// END_SYSEX					
sendchar( 0xF7 );

sendchar( "\r\n" );


function sendchar($char) {
	echo chr($char);
}
?>
