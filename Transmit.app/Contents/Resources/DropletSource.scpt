on open names
try
###server-password-creation###
on error errMsg number errorNumber
display dialog "An unknown error occurred:  " & errorNumber as text
return
end try

	tell application "System Events"
		set myProcesses to every process whose name is "Transmit"
		set wasRunning to (number of myProcesses is greater than 0)
	end tell

	tell application "Transmit"
			
			with timeout of 7200 seconds

				if number of documents is equal to 0 then
					set dropDocument to make new document
				else
					if ( wasRunning )
						set dropDocument to make new document at before front document
					else
						set dropDocument to front document
					end if
				end if

				tell current tab of dropDocument

					###connect-to-favorite-preflight###

					if ( ###connect-to-server-info### )
						try
							tell remote browser
                                set copiedURLs to ""

                                set firstUpload to true
                                repeat with the_item in names
                                    upload item at path the_item

									if ( ###should-copy-url### )

                                       if ( firstUpload is false ) then
                                            set copiedURLs to copiedURLs & "\n"
                                        end if

										set copy_path to root path
										set copy_path to copy_path & "/" & (my lastPathComponent(the_item as string))
										if ( create URL from path copy_path ) then
											set copiedURLs to copiedURLs & (the clipboard as string)
										end if

                                        set firstUpload to false

									end if

                                end repeat

                                if ( ###should-copy-url### )

                                	set the clipboard to (copiedURLs as string)

								end if
							
								close
							
							end tell
						end try
						
					end if
				
				end tell
				
				if ( wasRunning ) then
					close dropDocument
				else
					quit
				end if
			
			end timeout

		end tell

end open

on lastPathComponent(x)
if x is ":" then
	return ":"
end if
if item -1 of x is ":" then
set x to text 1 thru -2 of x
end if
set text item delimiters to ":"
return (text item -1 of x)
end lastPathComponent

on run
	tell application "System Events"
			set myProcesses to every process whose name is "Transmit"
			set wasRunning to (number of myProcesses is greater than 0)
	end tell

	tell application "Transmit"
			
			activate 
			
			###server-password-creation###

			with timeout of 7200 seconds
			
				if number of documents is equal to 0 then
					set dropDocument to make new document
				else
					if ( wasRunning )
						set dropDocument to make new document at before front document
					else
						set dropDocument to front document
					end if
				end if

				tell current tab of dropDocument

					###connect-to-favorite-preflight###

					###connect-to-server-info###
				
				end tell

			end timeout

	end tell

end run
