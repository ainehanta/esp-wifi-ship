
# simple http server written in powershell
#
$port = 8080

$root = "c:\work"
[console]::TreatControlCAsInput = $true
Write-Host "Simple Http Server start."

$listener = New-Object system.net.HttpListener
$listener.Prefixes.Add('http://127.0.0.1:'+$port+'/')
$listener.Start()
while($true) {

	if ([console]::KeyAvailable) {
		$key = [system.console]::readkey($true)
		if (($key.modifiers -band [consolemodifiers]"control") -and($key.key -eq "C")) {
			"Terminating..."
			break
		}
	}

	$context = $listener.GetContext() # block

$request = $context.Request

	$request.RawUrl

$path = $root + $request.RawUrl.Replace("/", "\");
$path

 	$response = $context.Response
 	if( Test-Path $path ) {
 		# 要求されたURLに対応するコンテンツを返す。
 		$page = Get-Content -Path $path
 	} else {
 		# 404
 		"404"
 		$page = Get-Content -Path c:\work\test.html
 	}
	# $var = read post/get var
	#$page = $page.Replace('%VAR%',$var)
	$buffer = [System.Text.Encoding]::UTF8.GetBytes($page)
	$response.ContentLength64 = $buffer.Length
	$output = $response.OutputStream
	$output.Write($buffer,0,$buffer.Length)

	$output.Close()
}

$listener.Stop()
