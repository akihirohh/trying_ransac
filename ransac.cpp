//Algorithm adapted from https://en.wikipedia.org/wiki/Random_sample_consensus


#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <vector>



	void ransac_demo(std::vector<double> x, std::vector<double> y, int minimun_num_pts, int iterations_num, double threshold_distance, double threshold_inliers_num, double &a, double &b)
	{
		int number = x.size();
		int best_line_inliers_num = 0;
		int rand_index, vec_rand_index[minimun_num_pts];
		std::vector<double> sample_x, sample_y;
		bool b_do_again = false;
    int inliers_num = 0;
    double distance;
    double k_line_norm_x, k_line_norm_y, k_line_x, k_line_y, norm, sx, sy;
		a = 0;
		b = 0;		
		
		for(int i  = 0; i < iterations_num; i++)
		{
			sample_x.clear();
			sample_y.clear();
			inliers_num = 0;

			int j = 0;			
			while(j < minimun_num_pts)
			{
				b_do_again = false;
				//randomly select 2 points
				srand(time(NULL));
				rand_index = rand()%number;		
				vec_rand_index[j]	= rand_index;	
				if(rand_index >= number) rand_index = number - 1;
				if(j > 0)
				{
					for ( int k = 0; k < j; k++ )
					{
						if(k != j && rand_index == vec_rand_index[k])
						{
							b_do_again = true;
						}
					}
				}
				if(!b_do_again) j++;
			}
      std::cout << "\niteration " << i << " rand_index[0]: " << vec_rand_index[0] << " rand_index[1]: " << vec_rand_index[1];

			for (int j = 0; j < minimun_num_pts; j++)
			{
				//Choose sample
				sample_x.push_back(x[vec_rand_index[j]]);
				sample_y.push_back(y[vec_rand_index[j]]);
        std::cout << "\nsample_x[" << j << "]: " << sample_x[j] << " sample_y[" << j << "]: " << sample_y[j];
			}
			k_line_x = sample_x[1] - sample_x[0];
			k_line_y = sample_y[1] - sample_y[0];
			norm = std::sqrt(pow(k_line_x,2) + pow(k_line_y,2));
			k_line_norm_x = k_line_x/norm;
			k_line_norm_y = k_line_y/norm;
      std::cout << "\nkLineNorm_x: " << k_line_norm_x << "\tkLineNorm_y: " << k_line_norm_y;
			sx = sample_x[0];
			sy = sample_y[0];
			for ( int j = 0; j < number; j++ )
			{
				distance = -k_line_norm_y*(x[j]-sx) + k_line_norm_x*(y[j]-sy) ;
        std::cout << "\ndistance[" << j << "]: " << distance;
				if(std::abs(distance) < threshold_distance)
				{
					inliers_num++;
				}
			}

			if(inliers_num > floor(threshold_inliers_num*number) && inliers_num > best_line_inliers_num)
			{
				best_line_inliers_num = inliers_num;
				a = (sample_y[1] - sample_y[0])/(sample_x[1] - sample_x[0]);
				b = sample_y[0] - a*sample_x[0];				
			}
      std::cout << "\na: " << a << "\tb: " << b;			
		}

	}

int main(int argc, char* argv[])
{
  std::vector<double> x, y;
  x.push_back(1);
  y.push_back(2.1);
  x.push_back(2.1);
  y.push_back(3);
  x.push_back(3.1);
  y.push_back(4);
  x.push_back(5.1);
  y.push_back(6);

  double a,b;
  ransac_demo(x,y,2,10,0.2,0.8,a,b);    

}