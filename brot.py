from time import sleep
width, height = 150, 50

zoom_level = 1
while True:
	print(chr(27) + "[2J")

	for y in range(height):
		for x in range(width):
			x_res, y_res = (x-width/1.5)/(4.0*zoom_level)-0.7463, (y-height/2)/(2.5*zoom_level)+0.1102
			c_x, c_y = [x_res, y_res][:]
			iter_count = None
			for iter in range(50):
				iter_count = iter
				if not -100 < x_res < 100 or not -100 < y_res < 100:
					break
				# print(x_res, y_res)
				x_res, y_res = x_res ** 2 - y_res ** 2 + c_x, 2 * x_res * y_res + c_y

			print("O" if iter_count > 40 else "o" if iter_count > 20 else "°" if iter_count > 10 else "." if iter_count > 6 else " ", end="")
		print()
	sleep(.2)
	zoom_level *= 1.05
