function [result] = ReadADC(channel)
s1 = serial('COM3', 'BaudRate', 19200);
fopen(s1);
fwrite(s1, ['a',channel,10]);
data = fread(s1, 2);
result = (data(1)*256 + data(2))*(4.65/1023);
fclose(s1);
end