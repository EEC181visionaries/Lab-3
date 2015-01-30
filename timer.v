//code for the timer if necessary
reg [15:0] counter1, [15:0] counter2, [15:0] nextcount1, [15:0] nexcount2;
reg [9:0] nexttime1, nexttime2, timer1, timer2;

always @(posedge CLOCK_50 or SW[1:0])
begin

	if(SW[1:0] == 2'b01)
		nextcount1 = counter1 + 1'b1;
	else
		nextcount1 = counter1;
	if(SW[1:0] == 2'b10)
		nextcount2 = counter2 + 1'b1;
	else
		nextcount2 = counter2;
	timer1 = nexttime1;
	timer2 = nexttime1;

end

always@(nextcount1 or nextcount2)
begin
	if(nextcount1 > 16'b1100001101010000 && timer < 10'b1111100110)
	begin
		counter1 = 16'b0;
		nexttime1 = timer + 1'b1;
	end
	else
	begin
		counter1 = nextcount1;
		nexttime1 = timer1;
	end

	if(counter2 > 16'b1100001101010000 && timer < 10'b1111100110)
	begin
		counter2 = 16'b0;
		nexttime2 = timer + 1'b1;
	end
	else
	begin
		counter1 = nextcount1;
		nexttime1 = timer1;
	end
end 
