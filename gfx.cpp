#include "gfx.h"

namespace PPM
{
	SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
	{
		// Loads a texture from file with SDL_image, no need for surface to texture conversion
		SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
		return texture;
	}
    
    SDL_Texture* renderText(std::string message, std::string fontFile, SDL_Color colour, int fontSize, SDL_Renderer *renderer)
    {
        //Open the font
        TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
        //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), colour);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        //Clean up unneeded stuff
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
    
        return texture;
    }

	// Non-stretch, original size rendering at position (x, y), whether flipped or not
	void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, bool facingRight)
	{
		// Destination rectangle of our desired position to render to
		SDL_Rect position;
		position.x = x;
		position.y = y;
		// Check texture for original width and height, use those instead of stretching upon render
		SDL_QueryTexture(tex, NULL, NULL, &position.w, &position.h);
		if (facingRight)
		{
			SDL_RenderCopy(renderer, tex, NULL, &position);
		}
		else
		{
			SDL_RenderCopyEx(renderer, tex, NULL, &position, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}

	// Stretches to size specified by width (w) and height (h) at position (x, y)
	void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y, int w, int h)
	{
		SDL_Rect position;
		position.x = x;
		position.y = y;
		position.w = w;
		position.h = h;
		SDL_RenderCopy(renderer, tex, NULL, &position);
	}
	
	// SDL_Rect based collision checking. 0 = No collision detected.
	// 1 = A is LEFT of B. 2 = A is RIGHT of B. 3 = A is BELOW B. 4 = A is ABOVE B.
	int checkCollision(SDL_Rect a, SDL_Rect b)
	{
		// Sides of the rectangles
		int left_a, right_a, top_a, bottom_a;
		int left_b, right_b, top_b, bottom_b;
		
		left_a = a.x;
		right_a = a.x + a.w;
		top_a = a.y;
		bottom_a = a.y + a.h;
		
		left_b = b.x;
		right_b = b.x + b.w;
		top_b = b.y;
		bottom_b = b.y + b.h;
		
		// Centre points, needed for direction checking
		int centre_a_x, centre_a_y, centre_b_x, centre_b_y;
		
		centre_a_x = a.x + (0.5 * a.w);
		centre_a_y = a.y + (0.5 * a.h);
		centre_b_x = b.x + (0.5 * b.w);
		centre_b_y = b.y + (0.5 * b.h);
		
		// Checks for A overlapping with B
		if (bottom_a <= top_b)
		{
			return false;
		}

		if (top_a >= bottom_b)
		{
			return false;
		}

		if (right_a <= left_b)
		{
			return false;
		}

		if (left_a >= right_b)
		{
			return false;
		}
		
		// Direction of collision - EXPERIMENTAL
		// Determine angle of line joining centre of A and B with x-axis
		float angle = atan2(centre_a_y - centre_b_y, centre_a_x - centre_b_x);
		angle = angle * (180 / 3.14); // convert to degrees, roughly
		
		//std::cout << "ANGLE = " << angle << std::endl; // DEBUG
		
		/*if (angle > -45 && angle < 45)
		{
			return 2; // A is to the RIGHT of B
		}
		else if (angle <= 135 && angle >= 45)
		{
			return 3; // A is BELOW B
		}
		else if (angle >= -135 && angle <= -45)
		{
			return 4; // A is ABOVE B
		}
		else
		{
			return 1; // A is to the LEFT of B
		}*/
        
        if (top_a < top_b && (angle > -150 && angle < -30))
        {
            return 4; // A above B
        }
        else if (bottom_a > bottom_b && (angle > 30 && angle < 150))
        {
            return 3; // A below B
        }
        else if (right_a > right_b && (angle > -60 && angle < 60))
        {
            return 2; // A right B
        }
        else if (left_a < left_b && (angle > 30 || angle < -30))
        {
            return 1; // A left B
        }

		return 5;
	}
}