# Computer-Graphics
8th Semester project for internal practical exam
Project Title: SPACE TRAVEL


1. Introduction


The SPACE TRAVEL project is a 2D animation simulation created using Computer Graphics techniques, depicting a complete space mission from Earth launch to planetary exploration and safe return. Implemented in C++ with the graphics.h library, this project visually demonstrates key concepts like object transformations, frame-by-frame animation, and orbital mechanics. Through nine interactive scenes—including rocket launch, solar system navigation, and astronaut spacewalk—it serves as a practical application of 2D graphics principles while simulating realistic space mission dynamics.

Tools Used:
Programming Language: C++
Graphics Library: graphics.h
IDE: Dev-C++ (configured with BGI support)

Purpose:
To illustrate 2D animations (translation, rotation, scaling)
To model physics-based motion (orbits, parabolic trajectories)
To showcase graphics.h functions for educational purposes




2. Objectives


Animation Implementation:
Create smooth 2D animations using primitive shapes (circles, rectangles, polygons) to depict the astronaut, rocket, planets, and celestial bodies.
Utilize frame-by-frame rendering techniques for lifelike motion sequences.

Physics Simulation:
Model real-world orbital mechanics using trigonometric functions (sin/cos) for planetary movements.
Simulate rocket launch dynamics with acceleration and parabolic trajectories.

Graphics Programming:
Master graphics.h functions including fillpoly(), fillellipse(), and putimage() for efficient rendering.
Implement double buffering (getimage()/putimage()) to eliminate screen flicker during animations.

Scene Composition:
Design 9 distinct scenes that collectively tell a cohesive visual story of a space mission.
Demonstrate hierarchical transformations (e.g., rocket rotating while orbiting a planet).




3. Code Overview


Scene-wise Implementation:
i)   Earth Launch: Animates an astronaut waving goodbye while a crowd cheers, using limb movement algorithms and randomized crowd animation.
ii)  Rocket Ascent: Simulates rocket launch with particle-based smoke effects and vertical acceleration physics.
iii) Space Transition: Renders a starfield background with parallax scrolling as the rocket enters orbit.
iv)  Solar System: Demonstrates planetary orbits using trigonometric functions (sin/cos) with scaled celestial bodies.
v)   Earth Orbit: Shows the rocket circling Earth with proper orbital mechanics and rotational transformation.
vi)  Spacewalk: Features an astronaut floating with tether physics and zero-gravity movement simulation.
vii) Re-entry: Animates rocket descent with atmospheric glow effects and heat distortion simulation.
viii)Landing: Depicts rocket touchdown with landing gear deployment and engine plume reduction.
ix)  Mission Success: Displays a cheering crowd with synchronized clapping animation and victory text overlay.

Algorithms Used:
-Trigonometric Motion: Planetary orbits (Scene 4) and waving animations (Scene 1) using sin()/cos()
-Frame Interpolation: Smooth movement in rocket launch (Scene 2) and spacewalk (Scene 6) via incremental position updates
-2D Transformations:
	=> Translation: Rocket trajectory (Scenes 2-3)
	=> Rotation: Planetary orbits (Scene 4) and spacecraft orientation (Scene 5)
	=> Scaling: Celestial body sizing (Scene 4)
-Particle Systems: Smoke/engine effects (Scenes 2,7) using randomized fillellipse() calls

Highlights:
Double buffering (getimage()/putimage()) for flicker-free animations
Modular scene architecture with dedicated functions per scene
Real-time user interaction handling via kbhit()




4. How to Run the Code


Tested Configuration:
-OS: Windows 10 (64-bit)
-Dev-C++: v5.11 (TDM-GCC 4.9.2)
-graphics.h: WinBGIm 6.0

Steps:
1.Install:
	-Install Dev-C++ 5.11 (with default TDM-GCC compiler)
	-Add graphics.h and libbgi.a to Dev-C++'s include and lib folders

2.Compile:
	g++ space_travel.cpp -o space_travel -lbgi -lgdi32 -luser32 -lshell32

3.Run:
	Execute space_travel.exe
	Press any key to skip scenes




5. Output Description


Scene 1: Earth Launch
	Visual: Blue sky, brown land with green grass
	Animation: Astronaut waves while walking toward rocket (ISRO-labeled)
	Crowd: 7 stick figures waving arms asynchronously

Scene 2: Rocket Launch
	Visual: Rocket ascends with white smoke particles
	Effect: Smoke dissipates upward as rocket accelerates

Scene 3: Space Transition
	Visual: Black background with 200+ white star pixels
	Rocket: Shrinks to 60% size while drifting horizontally

Scene 4: Solar System
	Visual: Quarter-sun (yellow sector) with 8 orbiting planets
	Detail: Earth has green continents, Saturn shows rings

Scene 5: Earth Orbit
	Visual: Earth (blue with continents) centered
	Rocket: Rotates while maintaining circular orbit

Scene 6: Spacewalk
	Visual: Astronaut floats with wavy tether physics
	Effect: Random drift within 230px boundary

Scene 7: Re-entry
	Visual: Rocket flips (engine-first) with yellow exhaust plume
	Background: Space with stars twinkling.

Scene 8: Landing
	Visual: Rocket descends with smoke trails
	Background: Blue sky background as rocket enters earth's atmosphere

Scene 9: Mission Accomplished
	Visual: Crowd of 10 clapping figures with text overlay:
	MISSION ACCOMPLISHED in white-on-blue



6. Challenges Faced


-Animation Flickering
	Issue: Screen tearing during scene transitions
	Solution: Implemented double buffering using:

		void *buffer = malloc(imagesize(0, 0, getmaxx(), getmaxy()));
		getimage(...); putimage(...);

-Crowd Synchronization
	Issue: Waving arms moved too uniformly
	Fix: Added randomized phases and speeds per character:

		float randomPhase = (rand() % 628) / 100.0f;  // 0-2π
		float randomSpeed = 0.01f + (rand() % 3)/100.0f;

-Orbit Calculations
	Issue: Planetary jitter during small angle increments
	Optimization: Used pre-calculated radians and global angle variables:

		mercuryAngle += 0.08f;  // Smoother than frame-dependent deltas

-Memory Leaks
	Issue: Background buffers not freed after scene transitions
	Debugged: Added free(spaceBackground) post-animation





7. Learning Outcomes


Through developing the SPACE TRAVEL animation, I gained hands-on experience with:

-2D Transformations
	Implemented translation (rocket movement), rotation (planetary orbits), and scaling (Earth/rocket size changes) using:
		setlinestyle(), rotatePoint(), fillellipse()

-Animation Principles
	Mastered frame-by-frame animation timing via delay()
	Achieved smooth motion using:
		Trigonometric functions (sin()/cos()) for orbits
		Linear interpolation for rocket trajectories

-graphics.h Mastery
	Practical use of 15+ functions including:
		getimage()/putimage() for flicker-free rendering
		fillpoly() for complex shapes (rocket, astronaut)
		setfillstyle() for color management

-Debugging Skills
	Resolved memory leaks in background buffers
	Optimized performance by reducing redundant cleardevice() calls

-System Integration
	Configured legacy graphics.h with modern Dev-C++




8. Conclusion


The SPACE TRAVEL project successfully demonstrates core Computer Graphics concepts through 9 interactive scenes, achieving:
	✔ Visual Accuracy: Realistic orbital mechanics using trigonometric calculations
	✔ Technical Implementation: 500+ lines of optimized C++ with graphics.h
	✔ Educational Value: helped in learning transformations, animations, clipping in computer graphics

Future Enhancements:
	-3D Projection: Implement Z-axis depth using perspective transforms
	-Audio Integration: Add launch sounds via PlaySound() (Windows API)
	-User Controls: Keyboard-interactive scene navigation
	-Advanced Effects: Particle systems for engine exhaust/starfields
