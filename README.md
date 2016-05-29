# phpscript

php `activescript` in php group has not been updated since 2004.

so copy it to here. and add fix some bugs.
## support PHP 5.2.6
other upgrade version not tested

## ActiveScript SAPI for PHP 
Allows you to use PHP as an ActiveScript engine from within other applications
Description.

This ActiveScript SAPI allows you to `embed PHP into your Windows applications` via the MS Scripting control, Windows Scripting Host or any other ActiveScript aware host application

Once registered on your system (using regsvr32), you will be able to use
PHP script in any ActiveScript compliant host.  The list includes:

*  Windows Script Host
*  ASP and ASP.NET
*  Windows Script Components / Behaviours
*  MS Scriptlet control

Probably the most useful of these will be using it with the scriptlet
control, or in your own activescript host, so that you can very easily
embed PHP into your win32 application.

### Installation.
Build and install it somewhere; then register the engine like this:

    regsvr32 php5activescript.dll

###Configuration.
PHPScript will not use the default php.ini file.
Instead, it will look only in the same directory as the .exe that caused it to
load.

You should create php-activescript.ini and place it in that folder, if you wish
to load extensions etc.

###Usage.
======

*  Windows Script Host

  Create a .wsf file like this:
```html
  <job id="test">
    <script language="PHPScript">
	  $WScript->Echo("Hello");
	</script>
  </job>
```
  
*  ASP and ASP.NET
```html
  <%@language=PHPScript %>
  <% $Response->Write("Hello"); %>
```
*  Windows Script Components / Behaviours

    Use language="PHPScript" on your < script > tags

*  MS Scriptlet control

    Set the language property to 'PHPScript'
  
### official 
The offical: http://pecl.php.net/package/PHPScript
