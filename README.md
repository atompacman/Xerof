# Xerof
## Setup developing environment
### Instructions for creating the Microsoft Visual Studio (2008-2013) project

- (1) File/New Project -> Templates/Visual C++ -> Empty Project. Create the project directly in the repository.

- (2) Copy those project properties "tel quel". Right click on the project -> Properties -> Configuration Properties
	  (make sure Configuration is set to "All configurations" and not "Debug"
  - Debugging/Environment <br>
      PATH=$(ProjectDir)\lib\allegro-5.0.10-msvc-11.0\bin;%PATH%
  - VC++ Directories/Include Directories <br>
      $(ProjectDir)\lib;$(ProjectDir)\lib\allegro-5.0.10-msvc-11.0\include;$(IncludePath)
  - VC++ Directories/References Directories <br>
      $(ProjectDir)\lib\allegro-5.0.10-msvc-11.0\lib;$(LibraryPath)
  - C/C++/General/Additional Include Directories <br>
      $(ProjectDir)\lib;$(ProjectDir)\lib\allegro-5.0.10-msvc-11.0\include;%(AdditionalIncludeDirectories) 
  - Linker/General/Additional Library Directories <br>
      $(ProjectDir)\lib\allegro-5.0.10-msvc-11.0\lib;%(AdditionalLibraryDirectories)
  - Linker/Input/Additional Dependence <br>
	  FOR "Debug" configuration:
	  add allegro-5.0.10-monolith-md-debug.lib;
	  FOR "Release" configuration
	  add allegro-5.0.10-monolith-md.lib;


## Development tools
### Logging
Use the following functions to log messages to console:

- LOG(LEVEL)
- LOG_IF(COND, LEVEL)
- LOG_EVERY_N(N, LEVEL)
- LOG_LEVEL_F(FORMAT, ARGS...)
- CHECK(COND)

Replace LEVEL by: TRACE, DEBUG, INFO or WARNING.

Ex.: LOG(INFO) << "Information";

*** Do not log "FATAL" level messages. Instead, use this:
FatalErrorDialog("Something important failed.");


### Max line length
The maximum length of lines of code is 80. Install this plugin to be able to add a guideline:
https://visualstudiogallery.msdn.microsoft.com/da227a0b-0e31-4a11-8f6b-3a149cf2e459
