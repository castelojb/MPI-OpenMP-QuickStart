

void printMatrix(double ** mat, int num){
    printf("Matriz:\n");
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            printf("%.1f, ", mat[i][j]);
        }
        printf("\n");
    }
}


unsigned char * gray_filter(unsigned char * rgb, int width, int height){

    size_t gray_img_size = width * height;

    unsigned char *gray_img = malloc(gray_img_size * sizeof(unsigned char));

	#pragma omp parallel for
	for(int x = 0; x < width; x++){

        for(int y = 0; y < height; y++){

            int idx =  (x * height) + y;
            
            int idx_red = (x*height*3 + y*3 + 0);
            
            int idx_green = (x*height*3 + y*3 + 1);

            int idx_blue = (x*height*3 + y*3 + 2);

            gray_img[idx] = (rgb[idx_red] * 0.2125) + (rgb[idx_green] * 0.7154) + (rgb[idx_blue] * 0.0721);
        }
    }
		
	return gray_img;
}


unsigned char * made_big_image(unsigned char * rgb, int image_size){

    size_t big_image_size = image_size * 4;

    unsigned char *big_image = malloc(big_image_size * sizeof(unsigned char));

	#pragma omp parallel for
	for(int image_frame = 0; image_frame < 4; image_frame++){

        for(int idx = 0; idx < image_size; idx++){

            int idx_on_big_image =  (image_frame * image_size) + idx;
            
            big_image[idx_on_big_image] = rgb[idx];
        }
    }
		
	return big_image;
}
