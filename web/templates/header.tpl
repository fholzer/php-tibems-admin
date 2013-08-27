{php} $contentType = strpos($_SERVER['HTTP_ACCEPT'], 'application/xhtml+xml') === false ? 'text/html' : 'application/xhtml+xml';
header("Content-Type: $contentType; charset=utf-8"); {/php}
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>Tibco EMS Adminweb</title>
	<link rel="stylesheet" href="style.css" type="text/css"/>
	<script type="text/javascript" src="js/prototype.js"></script>
	<script type="text/javascript" src="js/smarty_ajax.js"></script>
	<script type="text/javascript">
	function form_submit(originalResponse)
	{ldelim}
		document.getElementById('content').innerHTML = originalResponse.responseText;
	{rdelim}
	</script>

</head>
<body>
<div id="title">&nbsp;&nbsp;Tibco EMS Web Admin
<div id="ajax-process"></div>
<div id="login"><a style="text-decoration: none;" href="index.php?action=login">{$logindata}</a></div>
</div>