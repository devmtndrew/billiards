#include <raylib.h>
#include <raymath.h>

#include <iostream>
struct Circle
{
    Vector2 center; // Center of the circle
    Vector2 velocity; // Velocity of the circle
    float radius; // Radius of the circle
    float mass; // Mass of the circle
    float inverseMass; // Inverse mass (1 / mass) of the circle
};



int main()
{
    int windowWidth = 800, windowHeight = 600;
    InitWindow(windowWidth, windowHeight, "Billiards");

    const float TARGET_FPS = 60.0f;
    SetTargetFPS(TARGET_FPS);

    //Walls
    Rectangle boxA = { 60, 550, 680, 60 };
    Rectangle boxB = { 60, 0, 680, 50 };
    Rectangle boxC = { 0, 60, 50, 480 };
    Rectangle boxD = { 750, 60, 50, 480 };

    // Create cue ball
    Circle circleB;
    circleB.center.x = 100.0f;
    circleB.center.y = 290.0f;
    circleB.velocity.x = 0.0f;
    circleB.velocity.y = 0.0f;
    circleB.radius = 30.0f;
    circleB.mass = 1.0f;
    circleB.inverseMass = 1.0f / circleB.mass;    
    
    // Create first circle
    Circle circleA;
    circleA.center.x = 480.0f;
    circleA.center.y = 290.0f;
    circleA.velocity.x = 0.0f;
    circleA.velocity.y = 0.0f;
    circleA.radius = 30.0f;
    circleA.mass = 1.0f;
    circleA.inverseMass = 1.0f / circleA.mass;

    // create second circle
    Circle circleC;
    circleC.center.x = 550.0f;
    circleC.center.y = 250.0f;
    circleC.velocity.x = 0.0f;
    circleC.velocity.y = 0.0f;
    circleC.radius = 30.0f;
    circleC.mass = 1.0f;
    circleC.inverseMass = 1.0f / circleC.mass;

    // create second circle
    Circle circleD;
    circleD.center.x = 550.0f;
    circleD.center.y = 320.0f;
    circleD.velocity.x = 0.0f;
    circleD.velocity.y = 0.0f;
    circleD.radius = 30.0f;
    circleD.mass = 1.0f;
    circleD.inverseMass = 1.0f / circleD.mass;
    

    //pockets
    Circle circlePocketA;
    circlePocketA.center.x = 50.0f;
    circlePocketA.center.y = 50.0f;
    circlePocketA.velocity.x = 0.0f;
    circlePocketA.velocity.y = 0.0f;
    circlePocketA.radius = 50.0f;
    circlePocketA.mass = 1.0f;
    circlePocketA.inverseMass = 1.0f / circlePocketA.mass;

    Circle circlePocketB;
    circlePocketB.center.x = 750.0f;
    circlePocketB.center.y = 50.0f;
    circlePocketB.velocity.x = 0.0f;
    circlePocketB.velocity.y = 0.0f;
    circlePocketB.radius = 50.0f;
    circlePocketB.mass = 1.0f;
    circlePocketB.inverseMass = 1.0f / circlePocketB.mass;

    Circle circlePocketC;
    circlePocketC.center.x = 50.0f;
    circlePocketC.center.y = 550.0f;
    circlePocketC.velocity.x = 0.0f;
    circlePocketC.velocity.y = 0.0f;
    circlePocketC.radius = 50.0f;
    circlePocketC.mass = 1.0f;
    circlePocketC.inverseMass = 1.0f / circlePocketC.mass;

    Circle circlePocketD;
    circlePocketD.center.x = 750.0f;
    circlePocketD.center.y = 550.0f;
    circlePocketD.velocity.x = 0.0f;
    circlePocketD.velocity.y = 0.0f;
    circlePocketD.radius = 50.0f;
    circlePocketD.mass = 1.0f;
    circlePocketD.inverseMass = 1.0f / circlePocketC.mass;


    // Vector for cursor
    Vector2 P;

    // Vector for cue

    //for circle movement

    float accumulator = 0.0f;
    float TIMESTEP = 1.0f / 60.0f;
    float elasticity = 1.0f; // We want objects to bounce

    //Create Rectangle walls
    Rectangle rectangleA;
    rectangleA.x = 100.0f;
    rectangleA.y = 20.0f;
    rectangleA.height = 80.0f;
    rectangleA.width = 600.0f;




    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(GREEN);

        if (circleB.velocity.x <= 2.0f && circleB.velocity.y <= 2.0f && circleA.velocity.x <= 2.0f && circleA.velocity.y <= 2.0f && circleC.velocity.x <= 2.0f && circleC.velocity.y  <= 2.0f && circleD.velocity.x <= 2.0f && circleD.velocity.y <= 2.0f)
        {
        // Set the player's position to the mouse position
        P = GetMousePosition();

        // Get the vector from the Cue (source) to the Cursor (destination)
        // Destination - source
        Vector2 EP = Vector2Subtract(P, circleB.center);

        // Draw a yellow line with thickness 5.0 starting from the enemy's position to the player's position.
        // For demonstration purposes, we will calculate the player's position as
        // the position of the enemy + the vector going in the direction from E to P
        Vector2 P_temp = Vector2Add(circleB.center, EP);
        
       
        
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) //add if velocity is 0 later
            {
                DrawLineEx(circleB.center, P, 5.0f, YELLOW);
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                circleB.velocity.x = -(EP.x);
                circleB.velocity.y = -(EP.y);
            }
        }

        // ----- Cue ball move ----
        
        float deltaTime = GetFrameTime();
    
        // Fixed timestep setup
        accumulator = accumulator + deltaTime;
        while (accumulator >= TIMESTEP)
        {
            accumulator = accumulator - TIMESTEP;

            // Move both circles based on semi-implicit Euler (no acceleration)

            //cue ball move

            circleB.center.x = circleB.center.x + circleB.velocity.x * TIMESTEP;
            circleB.center.y = circleB.center.y + circleB.velocity.y * TIMESTEP;

            //other balls

            circleA.center.x = circleA.center.x + circleA.velocity.x * TIMESTEP;
            circleA.center.y = circleA.center.y + circleA.velocity.y * TIMESTEP;

            circleC.center.x = circleC.center.x + circleC.velocity.x * TIMESTEP;
            circleC.center.y = circleC.center.y + circleC.velocity.y * TIMESTEP;

            circleD.center.x = circleD.center.x + circleD.velocity.x * TIMESTEP;
            circleD.center.y = circleD.center.y + circleD.velocity.y * TIMESTEP;

        }

// ----------------- Collisions ---
            // --- Check for intersection ---

            // Get the sum of the two circle's radii
            float radiusSum = circleA.radius + circleB.radius;
            // Square the sum of the two radius (x^2 = x * x)
            radiusSum = radiusSum * radiusSum;

            float radiusSum1 = circleB.radius + circleC.radius;
            radiusSum1 = radiusSum1 * radiusSum1;

            float radiusSum2 = circleA.radius + circleC.radius;
            radiusSum2 = radiusSum2 * radiusSum2;

            float radiusSum3 = circleA.radius + circleD.radius;
            radiusSum3 = radiusSum3 * radiusSum3;

            float radiusSum4 = circleB.radius + circleD.radius;
            radiusSum4 = radiusSum4 * radiusSum4;

            float radiusSum5 = circleC.radius + circleD.radius;
            radiusSum5 = radiusSum5 * radiusSum5;

            // Get the vector from B (source) to A (destination) via vector subtraction
            Vector2 D;
            D.x = circleA.center.x - circleB.center.x;
            D.y = circleA.center.y - circleB.center.y;

            Vector2 E; 
            E.x = circleB.center.x - circleC.center.x;
            E.y = circleB.center.y - circleC.center.y;

            Vector2 F;
            F.x = circleA.center.x - circleC.center.x;
            F.y = circleA.center.y - circleC.center.y;

            Vector2 G;
            G.x = circleA.center.x - circleD.center.x;
            G.y = circleA.center.y - circleD.center.y;

            Vector2 H;
            H.x = circleB.center.x - circleD.center.x;
            H.y = circleB.center.y - circleD.center.y;

            Vector2 I;
            I.x = circleD.center.x - circleC.center.x;
            I.y = circleD.center.y - circleC.center.y;
            // Get the squared magnitude of the vector
            // The squared magnitude is x^2 + y^2 (without the square root)
            float dist = D.x * D.x + D.y * D.y;

            float dist1 = E.x * E.x + E.y * E.y;

            float dist2 = F.x * F.x + F.y * F.y;

            float dist3 = G.x * G.x + G.y * G.y;

            float dist4 = H.x * H.x + H.y * H.y;

            float dist5 = I.x * I.x + I.y * I.y;

            // If the distance between the two circles is less than the sum of their radius,
            // there is an intersection
            if (dist <= radiusSum)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal = D;

                // Relative velocity from B to A
                Vector2 relativeVelocity;
                relativeVelocity.x = circleA.velocity.x - circleB.velocity.x;
                relativeVelocity.y = circleA.velocity.y - circleB.velocity.y;

                float dot = Vector2DotProduct(collisionNormal, relativeVelocity);
                if (dot < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator1 = 1 + elasticity;
                    float numerator2 = dot;

                    float denom1 = Vector2DotProduct(collisionNormal, collisionNormal);
                    float denom2 = circleA.inverseMass + circleB.inverseMass;

                    float j = -(numerator1 * numerator2) / (denom1 * denom2);
    
                    // Apply impulse to both circle's velocities
                    circleA.velocity.x = circleA.velocity.x + j * circleA.inverseMass * collisionNormal.x;
                    circleA.velocity.y = circleA.velocity.y + j * circleA.inverseMass * collisionNormal.y;

                    circleB.velocity.x = circleB.velocity.x - j * circleB.inverseMass * collisionNormal.x;
                    circleB.velocity.y = circleB.velocity.y - j * circleB.inverseMass * collisionNormal.y;
                }
            }

            if (dist1 <= radiusSum1)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal1 = E;

                // Relative velocity from B to A
                Vector2 relativeVelocity1;
                relativeVelocity1.x = circleB.velocity.x - circleC.velocity.x;
                relativeVelocity1.y = circleB.velocity.y - circleC.velocity.y;

                float dot1 = Vector2DotProduct(collisionNormal1, relativeVelocity1);
                if (dot1 < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator3 = 1 + elasticity;
                    float numerator4 = dot1;

                    float denom3 = Vector2DotProduct(collisionNormal1, collisionNormal1);
                    float denom4 = circleB.inverseMass + circleC.inverseMass;

                    float k = -(numerator3 * numerator4) / (denom3 * denom4);
    
                    // Apply impulse to both circle's velocities
                    circleB.velocity.x = circleB.velocity.x + k * circleB.inverseMass * collisionNormal1.x;
                    circleB.velocity.y = circleB.velocity.y + k * circleB.inverseMass * collisionNormal1.y;

                    circleC.velocity.x = circleC.velocity.x - k * circleC.inverseMass * collisionNormal1.x;
                    circleC.velocity.y = circleC.velocity.y - k * circleC.inverseMass * collisionNormal1.y;
                }
            }

            if (dist2 <= radiusSum2)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal2 = F;

                // Relative velocity from B to A
                Vector2 relativeVelocity2;
                relativeVelocity2.x = circleA.velocity.x - circleC.velocity.x;
                relativeVelocity2.y = circleA.velocity.y - circleC.velocity.y;

                float dot2 = Vector2DotProduct(collisionNormal2, relativeVelocity2);
                if (dot2 < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator5 = 1 + elasticity;
                    float numerator6 = dot2;

                    float denom5 = Vector2DotProduct(collisionNormal2, collisionNormal2);
                    float denom6 = circleA.inverseMass + circleC.inverseMass;

                    float l = -(numerator5 * numerator6) / (denom5 * denom6);
    
                    // Apply impulse to both circle's velocities
                    circleA.velocity.x = circleA.velocity.x + l * circleA.inverseMass * collisionNormal2.x;
                    circleA.velocity.y = circleA.velocity.y + l * circleA.inverseMass * collisionNormal2.y;

                    circleC.velocity.x = circleC.velocity.x - l * circleC.inverseMass * collisionNormal2.x;
                    circleC.velocity.y = circleC.velocity.y - l * circleC.inverseMass * collisionNormal2.y;
                }
            }

            if (dist3 <= radiusSum3)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal3 = G;

                // Relative velocity from B to A
                Vector2 relativeVelocity3;
                relativeVelocity3.x = circleA.velocity.x - circleD.velocity.x;
                relativeVelocity3.y = circleA.velocity.y - circleD.velocity.y;

                float dot3 = Vector2DotProduct(collisionNormal3, relativeVelocity3);
                if (dot3 < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator7 = 1 + elasticity;
                    float numerator8 = dot3;

                    float denom7 = Vector2DotProduct(collisionNormal3, collisionNormal3);
                    float denom8 = circleA.inverseMass + circleD.inverseMass;

                    float m = -(numerator7 * numerator8) / (denom7 * denom8);
    
                    // Apply impulse to both circle's velocities
                    circleA.velocity.x = circleA.velocity.x + m * circleA.inverseMass * collisionNormal3.x;
                    circleA.velocity.y = circleA.velocity.y + m * circleA.inverseMass * collisionNormal3.y;

                    circleD.velocity.x = circleD.velocity.x - m * circleD.inverseMass * collisionNormal3.x;
                    circleD.velocity.y = circleD.velocity.y - m * circleD.inverseMass * collisionNormal3.y;
                }
            }

            if (dist4 <= radiusSum4)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal4 = H;

                // Relative velocity from B to A
                Vector2 relativeVelocity4;
                relativeVelocity4.x = circleB.velocity.x - circleD.velocity.x;
                relativeVelocity4.y = circleB.velocity.y - circleD.velocity.y;

                float dot4 = Vector2DotProduct(collisionNormal4, relativeVelocity4);
                if (dot4 < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator9 = 1 + elasticity;
                    float numerator10 = dot4;

                    float denom9 = Vector2DotProduct(collisionNormal4, collisionNormal4);
                    float denom10 = circleB.inverseMass + circleD.inverseMass;

                    float n = -(numerator9 * numerator10) / (denom9 * denom10);
    
                    // Apply impulse to both circle's velocities
                    circleB.velocity.x = circleB.velocity.x + n * circleB.inverseMass * collisionNormal4.x;
                    circleB.velocity.y = circleB.velocity.y + n * circleB.inverseMass * collisionNormal4.y;

                    circleD.velocity.x = circleD.velocity.x - n * circleD.inverseMass * collisionNormal4.x;
                    circleD.velocity.y = circleD.velocity.y - n * circleD.inverseMass * collisionNormal4.y;
                }
            }

            if (dist5 <= radiusSum5)
            {
                // --- Check if actually colliding ---
                Vector2 collisionNormal5 = I;

                // Relative velocity from B to A
                Vector2 relativeVelocity5;
                relativeVelocity5.x = circleD.velocity.x - circleC.velocity.x;
                relativeVelocity5.y = circleD.velocity.y - circleC.velocity.y;

                float dot5 = Vector2DotProduct(collisionNormal5, relativeVelocity5);
                if (dot5 < 0.0f) // Colliding if A is moving towards B
                {
                    // Calculate for impulse (j)
                    float numerator11 = 1 + elasticity;
                    float numerator12 = dot5;

                    float denom11 = Vector2DotProduct(collisionNormal5, collisionNormal5);
                    float denom12 = circleC.inverseMass + circleD.inverseMass;

                    float o = -(numerator11 * numerator12) / (denom11 * denom12);
    
                    // Apply impulse to both circle's velocities
                    circleD.velocity.x = circleD.velocity.x + o * circleD.inverseMass * collisionNormal5.x;
                    circleD.velocity.y = circleD.velocity.y + o * circleD.inverseMass * collisionNormal5.y;

                    circleC.velocity.x = circleC.velocity.x - o * circleC.inverseMass * collisionNormal5.x;
                    circleC.velocity.y = circleC.velocity.y - o * circleC.inverseMass * collisionNormal5.y;
                }
            }


            float friction = 0.45f;

            circleA.velocity.x = circleA.velocity.x - friction / circleA.mass * circleA.velocity.x * TIMESTEP;
			circleA.velocity.y = circleA.velocity.y - friction / circleA.mass * circleA.velocity.y * TIMESTEP;

            circleB.velocity.x = circleB.velocity.x - friction / circleB.mass * circleB.velocity.x * TIMESTEP;
			circleB.velocity.y = circleB.velocity.y - friction / circleB.mass * circleB.velocity.y * TIMESTEP;

            circleC.velocity.x = circleC.velocity.x - friction / circleC.mass * circleC.velocity.x * TIMESTEP;
			circleC.velocity.y = circleC.velocity.y - friction / circleC.mass * circleC.velocity.y * TIMESTEP;

            circleD.velocity.x = circleD.velocity.x - friction / circleD.mass * circleD.velocity.x * TIMESTEP;
			circleD.velocity.y = circleD.velocity.y - friction / circleD.mass * circleD.velocity.y * TIMESTEP;
                

//-------------POCKETS----------------------------

        // POCKET A---

        // cue ball Pocket A
        //checking for intersection
        // Get the sum of the two circle's radii
        float radiusSumPocketA = circleB.radius + circlePocketA.radius;
        // Square the sum of the two radius (x^2 = x * x)
        radiusSumPocketA = radiusSumPocketA * radiusSumPocketA;

        // Get the vector from A (source) to Pocket (destination) via vector subtraction
        Vector2 DPocketA;
        DPocketA.x = circlePocketA.center.x - circleB.center.x;
        DPocketA.y = circlePocketA.center.y - circleB.center.y;

        // Get the squared magnitude of the vector
        // The squared magnitude is x^2 + y^2 (without the square root)
        float distPocketA = DPocketA.x * DPocketA.x + DPocketA.y * DPocketA.y;
        // If the distance between the two circles is less than the sum of their radius,
        // there is an intersection
        if (distPocketA <= radiusSumPocketA)
        {
            circleB.center.x = 200.0f;
            circleB.center.y = 200.0f;
            circleB.velocity.x = 0.0f;
            circleB.velocity.y = 0.0f;
        }

        //ball A Pocket A
        float radiusSumPocketA2 = circleA.radius + circlePocketA.radius;
        radiusSumPocketA2 = radiusSumPocketA2 * radiusSumPocketA2;

        Vector2 DPocket2A;
        DPocket2A.x = circlePocketA.center.x - circleA.center.x;
        DPocket2A.y = circlePocketA.center.y - circleA.center.y;

        float distPocket2A = DPocket2A.x * DPocket2A.x + DPocket2A.y * DPocket2A.y;

        if (distPocket2A <= radiusSumPocketA2)
        {
            circleA.center.x = 1000.0f;
            circleA.center.y = 1000.0f;
        }

        //ball C Pocket A
        float radiusSumPocketA3 = circleC.radius + circlePocketA.radius;
        radiusSumPocketA3 = radiusSumPocketA3 * radiusSumPocketA3;

        Vector2 DPocket3A;
        DPocket3A.x = circlePocketA.center.x - circleC.center.x;
        DPocket3A.y = circlePocketA.center.y - circleC.center.y;

        float distPocket3A = DPocket3A.x * DPocket3A.x + DPocket3A.y * DPocket3A.y;

        if (distPocket3A <= radiusSumPocketA3)
        {
            circleC.center.x = 1000.0f;
            circleC.center.y = 1000.0f;
        }

        //ball D Pocket A
        float radiusSumPocketA4 = circleD.radius + circlePocketA.radius;
        radiusSumPocketA4 = radiusSumPocketA4 * radiusSumPocketA4;

        Vector2 DPocket4A;
        DPocket4A.x = circlePocketA.center.x - circleD.center.x;
        DPocket4A.y = circlePocketA.center.y - circleD.center.y;

        float distPocket4A = DPocket4A.x * DPocket4A.x + DPocket4A.y * DPocket4A.y;

        if (distPocket4A <= radiusSumPocketA4)
        {
            circleD.center.x = 1000.0f;
            circleD.center.y = 1000.0f;
        }


        //---POCKET B----

        // cue ball Pocket B

        float radiusSumPocketB = circleB.radius + circlePocketB.radius;

        radiusSumPocketB = radiusSumPocketB * radiusSumPocketB;

        Vector2 DPocketB;
        DPocketB.x = circlePocketB.center.x - circleB.center.x;
        DPocketB.y = circlePocketB.center.y - circleB.center.y;


        float distPocketB = DPocketB.x * DPocketB.x + DPocketB.y * DPocketB.y;

        if (distPocketB <= radiusSumPocketB)
        {
            circleB.center.x = 200.0f;
            circleB.center.y = 200.0f;
            circleB.velocity.x = 0.0f;
            circleB.velocity.y = 0.0f;
        }

        //ball A Pocket B
        float radiusSumPocketB2 = circleA.radius + circlePocketB.radius;
        radiusSumPocketB2 = radiusSumPocketB2 * radiusSumPocketB2;

        Vector2 DPocket2B;
        DPocket2B.x = circlePocketB.center.x - circleA.center.x;
        DPocket2B.y = circlePocketB.center.y - circleA.center.y;

        float distPocket2B = DPocket2B.x * DPocket2B.x + DPocket2B.y * DPocket2B.y;

        if (distPocket2B <= radiusSumPocketB2)
        {
            circleA.center.x = 1000.0f;
            circleA.center.y = 1000.0f;
        }

        //ball C Pocket B
        float radiusSumPocketB3 = circleC.radius + circlePocketB.radius;
        radiusSumPocketB3 = radiusSumPocketB3 * radiusSumPocketB3;

        Vector2 DPocket3B;
        DPocket3B.x = circlePocketB.center.x - circleC.center.x;
        DPocket3B.y = circlePocketB.center.y - circleC.center.y;

        float distPocket3B = DPocket3B.x * DPocket3B.x + DPocket3B.y * DPocket3B.y;

        if (distPocket3B <= radiusSumPocketB3)
        {
            circleC.center.x = 1000.0f;
            circleC.center.y = 1000.0f;
        }

        //ball D Pocket B
        float radiusSumPocketB4 = circleD.radius + circlePocketB.radius;
        radiusSumPocketB4 = radiusSumPocketB4 * radiusSumPocketB4;

        Vector2 DPocket4B;
        DPocket4B.x = circlePocketB.center.x - circleD.center.x;
        DPocket4B.y = circlePocketB.center.y - circleD.center.y;

        float distPocket4B = DPocket4B.x * DPocket4B.x + DPocket4B.y * DPocket4B.y;

        if (distPocket4B <= radiusSumPocketB4)
        {
            circleD.center.x = 1000.0f;
            circleD.center.y = 1000.0f;
        }

         //---POCKET C----

        // cue ball Pocket C

        float radiusSumPocketC = circleB.radius + circlePocketC.radius;

        radiusSumPocketC = radiusSumPocketC * radiusSumPocketC;

        Vector2 DPocketC;
        DPocketC.x = circlePocketC.center.x - circleB.center.x;
        DPocketC.y = circlePocketC.center.y - circleB.center.y;


        float distPocketC = DPocketC.x * DPocketC.x + DPocketC.y * DPocketC.y;

        if (distPocketC <= radiusSumPocketC)
        {
            circleB.center.x = 200.0f;
            circleB.center.y = 200.0f;
            circleB.velocity.x = 0.0f;
            circleB.velocity.y = 0.0f;
        }

        //ball A Pocket C
        float radiusSumPocketC2 = circleA.radius + circlePocketC.radius;
        radiusSumPocketC2 = radiusSumPocketC2 * radiusSumPocketC2;

        Vector2 DPocket2C;
        DPocket2C.x = circlePocketC.center.x - circleA.center.x;
        DPocket2C.y = circlePocketC.center.y - circleA.center.y;

        float distPocket2C = DPocket2C.x * DPocket2C.x + DPocket2C.y * DPocket2C.y;

        if (distPocket2C <= radiusSumPocketC2)
        {
            circleA.center.x = 1000.0f;
            circleA.center.y = 1000.0f;
        }

        //ball C Pocket C
        float radiusSumPocketC3 = circleC.radius + circlePocketC.radius;
        radiusSumPocketC3 = radiusSumPocketC3 * radiusSumPocketC3;

        Vector2 DPocket3C;
        DPocket3C.x = circlePocketC.center.x - circleC.center.x;
        DPocket3C.y = circlePocketC.center.y - circleC.center.y;

        float distPocket3C = DPocket3C.x * DPocket3C.x + DPocket3C.y * DPocket3C.y;

        if (distPocket3C <= radiusSumPocketC3)
        {
            circleC.center.x = 1000.0f;
            circleC.center.y = 1000.0f;
        }

        //ball D Pocket C
        float radiusSumPocketC4 = circleD.radius + circlePocketC.radius;
        radiusSumPocketC4 = radiusSumPocketC4 * radiusSumPocketC4;

        Vector2 DPocket4C;
        DPocket4C.x = circlePocketC.center.x - circleD.center.x;
        DPocket4C.y = circlePocketC.center.y - circleD.center.y;

        float distPocket4C = DPocket4C.x * DPocket4C.x + DPocket4C.y * DPocket4C.y;

        if (distPocket4C <= radiusSumPocketC4)
        {
            circleD.center.x = 1000.0f;
            circleD.center.y = 1000.0f;
        }

        //---POCKET D----

        // cue ball Pocket D

        float radiusSumPocketD = circleB.radius + circlePocketD.radius;

        radiusSumPocketD = radiusSumPocketD * radiusSumPocketD;

        Vector2 DPocketD;
        DPocketD.x = circlePocketD.center.x - circleB.center.x;
        DPocketD.y = circlePocketD.center.y - circleB.center.y;


        float distPocketD = DPocketD.x * DPocketD.x + DPocketD.y * DPocketD.y;

        if (distPocketD <= radiusSumPocketD)
        {
            circleB.center.x = 200.0f;
            circleB.center.y = 200.0f;
            circleB.velocity.x = 0.0f;
            circleB.velocity.y = 0.0f;
        }

        //ball A Pocket D
        float radiusSumPocketD2 = circleA.radius + circlePocketD.radius;
        radiusSumPocketD2 = radiusSumPocketD2 * radiusSumPocketD2;

        Vector2 DPocket2D;
        DPocket2D.x = circlePocketD.center.x - circleA.center.x;
        DPocket2D.y = circlePocketD.center.y - circleA.center.y;

        float distPocket2D = DPocket2D.x * DPocket2D.x + DPocket2D.y * DPocket2D.y;

        if (distPocket2D <= radiusSumPocketD2)
        {
            circleA.center.x = 1000.0f;
            circleA.center.y = 1000.0f;
        }

        //ball C Pocket D
        float radiusSumPocketD3 = circleC.radius + circlePocketD.radius;
        radiusSumPocketD3 = radiusSumPocketD3 * radiusSumPocketD3;

        Vector2 DPocket3D;
        DPocket3D.x = circlePocketD.center.x - circleC.center.x;
        DPocket3D.y = circlePocketD.center.y - circleC.center.y;

        float distPocket3D = DPocket3D.x * DPocket3D.x + DPocket3D.y * DPocket3D.y;

        if (distPocket3D <= radiusSumPocketD3)
        {
            circleC.center.x = 1000.0f;
            circleC.center.y = 1000.0f;
        }

        //ball D Pocket B
        float radiusSumPocketD4 = circleD.radius + circlePocketD.radius;
        radiusSumPocketD4 = radiusSumPocketD4 * radiusSumPocketD4;

        Vector2 DPocket4D;
        DPocket4D.x = circlePocketD.center.x - circleD.center.x;
        DPocket4D.y = circlePocketD.center.y - circleD.center.y;

        float distPocket4D = DPocket4D.x * DPocket4D.x + DPocket4D.y * DPocket4D.y;

        if (distPocket4D <= radiusSumPocketD4)
        {
            circleD.center.x = 1000.0f;
            circleD.center.y = 1000.0f;
        }

        


// ------------------------ WALLS --------------------
        if ((circleA.center.x >= (GetScreenWidth() - circleA.radius - 50)) || (circleA.center.x <= circleA.radius + 50)) circleA.velocity.x *= -1.0f;
        if ((circleA.center.y >= (GetScreenHeight() - circleA.radius -50)) || (circleA.center.y <= circleA.radius + 50)) circleA.velocity.y *= -1.0f;

        if ((circleB.center.x >= (GetScreenWidth() - circleB.radius - 50)) || (circleB.center.x <= circleB.radius + 50)) circleB.velocity.x *= -1.0f;
        if ((circleB.center.y >= (GetScreenHeight() - circleB.radius -50)) || (circleB.center.y <= circleB.radius + 50)) circleB.velocity.y *= -1.0f;

        if ((circleC.center.x >= (GetScreenWidth() - circleC.radius - 50)) || (circleC.center.x <= circleC.radius + 50)) circleC.velocity.x *= -1.0f;
        if ((circleC.center.y >= (GetScreenHeight() - circleC.radius -50)) || (circleC.center.y <= circleC.radius + 50)) circleC.velocity.y *= -1.0f;

        if ((circleD.center.x >= (GetScreenWidth() - circleD.radius - 50)) || (circleD.center.x <= circleD.radius + 50)) circleD.velocity.x *= -1.0f;
        if ((circleD.center.y >= (GetScreenHeight() - circleD.radius -50)) || (circleD.center.y <= circleD.radius + 50)) circleD.velocity.y *= -1.0f;


//------------RESET-----------------     
        if (IsKeyPressed(KEY_R))
        {
            circleB.center.x = 100.0f;
            circleB.center.y = 290.0f;
            circleB.velocity.x = 0.0f;
            circleB.velocity.y = 0.0f;
            
            circleA.center.x = 480.0f;
            circleA.center.y = 290.0f;
            circleA.velocity.x = 0.0f;
            circleA.velocity.y = 0.0f;

            circleC.center.x = 550.0f;
            circleC.center.y = 250.0f;
            circleC.velocity.x = 0.0f;
            circleC.velocity.y = 0.0f;

            circleD.center.x = 550.0f;
            circleD.center.y = 320.0f;
            circleD.velocity.x = 0.0f;
            circleD.velocity.y = 0.0f;
    
        }

        // Draw Balls

        DrawCircleV(circleB.center, circleB.radius, WHITE);

        DrawCircleV(circleD.center, circleD.radius, YELLOW);
        DrawCircleV(circleA.center, circleA.radius, PINK);
        DrawCircleV(circleC.center, circleC.radius, RED);



        //Draw Walls
        DrawRectangleRec(boxA, BROWN);
        DrawRectangleRec(boxB, BROWN);
        DrawRectangleRec(boxC, BROWN);
        DrawRectangleRec(boxD, BROWN);

        //Draw Pockets
        DrawCircleV(circlePocketA.center, circlePocketA.radius, BLACK);
        DrawCircleV(circlePocketB.center, circlePocketB.radius, BLACK);
        DrawCircleV(circlePocketC.center, circlePocketC.radius, BLACK);
        DrawCircleV(circlePocketD.center, circlePocketD.radius, BLACK);

      

        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}


//g++ name.cpp -o out -I raylib/ -L raylib/ -lraylib -lopengl32 -lgdi32 -lwinmm
