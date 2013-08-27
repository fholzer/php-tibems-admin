<?php

session_start();
require_once 'includes/functions.inc.php';
include 'serverlist.conf.php';

$ss = new SecureSession();
$ss->check_browser = true;
$ss->check_ip_blocks = 2;
if(isset($_POST['uname']) && isset($_POST['server']))
{
	$_SESSION['uname'] = $_POST['uname'];
	$_SESSION['passwd'] = $_POST['passwd'];
	if(strlen($_POST['serverlist']) > 3) {
		$_SESSION['server'] = $_POST['serverlist'];
	}else{
		$_SESSION['server'] = $_POST['server'];
	}
	$_SESSION['loggedin'] = true;
	$ss->Open();
	header('Location: index.php');
	die();
}

if(!isset($_SESSION['uname']) || !isset($_SESSION['server']))
{
	$_GET['action'] = 'login';
}

if($ss->Check() && $_GET['action'] != 'login')
{
	$connection = new Tibco($_SESSION['server'], $_SESSION['uname'], $_SESSION['passwd']);
	if(!$connection->connect())
	{
		$error = 'Incorrect username or password.';
		$_GET['action'] = 'login';
	}
}

switch($_GET['action'])
{
	case 'login':
		$username = $_SESSION['uname'];
		$serverurl = isset($_SESSION['server'])?$_SESSION['server']:'tcp://';
		$ss->UnregisterAll();
		$smarty->assign('error',$error);
		$smarty->assign('uname',$username);
		$smarty->assign('server',$serverurl);
		$smarty->assign('data',$serverlist);
    break;
	default:
		$_GET['action'] = 'index';
		break;
}
if($_SESSION['loggedin'] == true)
	$smarty->assign('logindata',$_SESSION['uname'].'@'.$_SESSION['server']);
$smarty->assign('version', tibcoadm_version());
$smarty->display($_GET['action'].'.tpl');
?>
