<?php

require_once 'includes/smarty/Smarty.class.php';

$smarty = new Smarty;

$smarty->compile_check = true;
$smarty->debugging = false;
$smarty->caching = false;
$smarty->cache_lifetime = -1;
#$smarty->debugging = true;
$ajax_export_list = array();

ajax_register('getContent');
ajax_register('getSubContent');
ajax_process_call();

function __autoload($class_name) {
    require_once 'includes/' . $class_name . '.class.php';
}

function ajax_register() {
  global $ajax_export_list;

  $n = func_num_args();
  for ($i = 0; $i < $n; $i++) {
  	$ajax_export_list[] = func_get_arg($i);
  }
}

function ajax_process_call() {
  global $ajax_export_list;

  if (!isset($_REQUEST['f'])) return;
  $function = $_REQUEST['f'];
  if (false !== array_search($function, $ajax_export_list)) call_user_func($function);
  exit();
}

function bytes($a) {
    $unim = array("B","KiB","MiB","GiB","TiB","PiB");
    $c = 0;
    while ($a>=1024) {
        $c++;
        $a = $a/1024;
    }
    return number_format($a,($c ? 2 : 0),",",".").$unim[$c];
}

function dateDifference($start_timestamp,$end_timestamp){
	$days_seconds_star=(23 * 56 * 60) + 4.091; // Star Day
	$days_seconds_sun=24 * 60 * 60; // Sun Day
	$difference_seconds=round(($end_timestamp - $start_timestamp) / 1000,2);
	$difference_days=round(($difference_seconds / $days_seconds_sun),2);
	if($difference_days > 1)
		return $difference_days.' Days';
	$difference_hours=round(($difference_seconds / 3600),2);
	if($difference_hours > 1)
		return $difference_hours.' Hours';
	$difference_minutes=round(($difference_seconds / 60),2);
	if($difference_minutes > 1)
		return $difference_minutes.' Minutes';
	if($difference_seconds < 0)
		$difference_seconds = 0;
	return $difference_seconds.' Seconds';
}

function getContent() {
	global $smarty;
	
	$connection = new Tibco($_SESSION['server'], $_SESSION['uname'], $_SESSION['passwd']);
	if(!$connection->connect())
	{
		$error = 'Incorrect username or password.';
		$_GET['type'] = 'error';
	}
	switch($_GET['type'])
	{
		case 'queues':
			$smarty->assign('data',$connection->getQueues()->getAll());
			break;
		case 'topics':
			$smarty->assign('data',$connection->getTopics()->getAll());
			break;
		case 'durables':
			$smarty->assign('data',$connection->getDurables()->getAll());
			break;
		case 'connections':
			$smarty->assign('data',$connection->getConnections()->getAll());
			break;
		case 'consumers':
			$smarty->assign('data',$connection->getConsumers()->getAll());
			break;
		case 'producers':
			$smarty->assign('data',$connection->getProducers()->getAll());
			break;
		case 'transactions':
			$smarty->assign('data',$connection->getTransactions()->getAll());
			break;
		case 'jndinames':
			$smarty->assign('data',$connection->getJndiNames()->getAll());
			break;
		case 'users':
			$smarty->assign('data',$connection->getUsers()->getAll());
			break;
		case 'groups':
			$smarty->assign('data',$connection->getGroups()->getAll());
			break;
		case 'group':
			$smarty->assign('name',$_GET['name']);
			$smarty->assign('data',$connection->getGroup($_GET['name']));
			break;
		case 'permuser':
			$smarty->assign('name',$_GET['name']);
			$smarty->assign('data',$connection->getPermissions($_GET['name'])->getAll());
			break;
		case 'bridges':
			$smarty->assign('data',$connection->getBridges()->getAll());
			break;
		case 'bridge':
			$data = $connection->getBridge($_GET['src'],$_GET['srctype']);
			$smarty->assign('src',$data['source']);
			$smarty->assign('data',$data['targets']);
			break;
		case 'factories':
			$smarty->assign('data',$connection->getFactories()->getAll());
			break;
		case 'routes':
			$smarty->assign('data',$connection->getRoutes()->getAll());
			break;
		case 'status':
			$smarty->assign('Serverstatus',$connection->getStatus());
			break;
		default:
			$_GET['type'] = 'error';
			break;
	}
	$smarty->display($_GET['type'].'.tpl');
}

function getSubContent() {
	global $smarty;
	
	$connection = new Tibco($_SESSION['server'], $_SESSION['uname'], $_SESSION['passwd']);
	if(!$connection->connect())
	{
		$error = 'Incorrect username or password.';
		$_GET['type'] = 'error';
	}
	switch($_GET['type'])
	{
		case 'delconnection':
			$connection->removeConnection($_GET['connid']);
			$smarty->assign('data',$connection->getConnections()->getAll());
			$exitpage='connections';
			break;
		case 'delqueue':
			$connection->removeQueue($_GET['name']);
			$smarty->assign('data',$connection->getQueues()->getAll());
			$exitpage='queues';
			break;
		case 'purgequeue':
			$connection->purgeQueue($_GET['name']);
			$smarty->assign('data',$connection->getQueues()->getAll());
			$exitpage='queues';
			break;
		case 'createqueue':
			if($_GET['do'] == 1) {
				$connection->createQueue($_POST['name'], $_POST['prefetch'], $_POST['overflow'], $_POST['redelivery'], $_POST['maxbytes'], $_POST['maxmsgs'], $_POST['expiration'], $_POST['flowcontrol'], $_POST['failsafe'], $_POST['secure'], $_POST['isglobal'], $_POST['sname'], $_POST['snameenf'], $_POST['exclusive']);
				$exitpage='queues';
				$smarty->assign('data',$connection->getQueues()->getAll());
			}else{
				$exitpage='createqueue';
			}
			break;
		case 'editqueue':
			if($_GET['do'] == 1) {
				$connection->editQueue($_POST['name'], $_POST['prefetch'], $_POST['overflow'], $_POST['redelivery'], $_POST['maxbytes'], $_POST['maxmsgs'], $_POST['expiration'], $_POST['flowcontrol'], $_POST['failsafe'], $_POST['secure'], $_POST['isglobal'], $_POST['sname'], $_POST['snameenf'], $_POST['exclusive']);
				$exitpage='queues';
				$smarty->assign('data',$connection->getQueues()->getAll());
			}else{
				$smarty->assign('data',$connection->getQueue($_GET['name']));
				$exitpage='editqueue';
			}
			break;
		case 'deltopic':
			$connection->removeTopic($_GET['name']);
			$smarty->assign('data',$connection->getTopics()->getAll());
			$exitpage='topics';
			break;
		case 'purgetopic':
			$connection->purgeTopic($_GET['name']);
			$smarty->assign('data',$connection->getTopics()->getAll());
			$exitpage='topics';
			break;
		case 'createtopic':
			if($_GET['do'] == 1) {
				$connection->createTopic($_POST['name'], $_POST['prefetch'], $_POST['overflow'], $_POST['maxbytes'], $_POST['maxmsgs'], $_POST['expiration'], $_POST['flowcontrol'], $_POST['failsafe'], $_POST['secure'], $_POST['isglobal'], $_POST['sname'], $_POST['snameenf']);
				$exitpage='topics';
				$smarty->assign('data',$connection->getTopics()->getAll());
			}else{
				$exitpage='createtopic';
			}
			break;
		case 'edittopic':
			if($_GET['do'] == 1) {
				$connection->editTopic($_POST['name'], $_POST['prefetch'], $_POST['overflow'], $_POST['maxbytes'], $_POST['maxmsgs'], $_POST['expiration'], $_POST['flowcontrol'], $_POST['failsafe'], $_POST['secure'], $_POST['isglobal'], $_POST['sname'], $_POST['snameenf']);
				$exitpage='topics';
				$smarty->assign('data',$connection->getTopics()->getAll());
			}else{
				$smarty->assign('data',$connection->getTopic($_GET['name']));
				$exitpage='edittopic';
			}
			break;
		case 'deldurable':
			$connection->removeDurable($_GET['name'], $_GET['clientid']);
			$smarty->assign('data',$connection->getDurables()->getAll());
			$exitpage='durables';
			break;
		case 'purgedurable':
			$connection->purgeDurable($_GET['name'], $_GET['clientid']);
			$smarty->assign('data',$connection->getDurables()->getAll());
			$exitpage='durables';
			break;
		case 'createdurable':
			if($_GET['do'] == 1) {
				$connection->createDurable($_POST['tname'], $_POST['name'], '');
				$exitpage='durables';
				$smarty->assign('data',$connection->getDurables()->getAll());
			}else{
				$exitpage='createdurable';
			}
			break;
		case 'deluser':
			$connection->removeUser($_GET['name']);
			$smarty->assign('data',$connection->getUsers()->getAll());
			$exitpage='users';
			break;
		case 'createuser':
			if($_GET['do'] == 1) {
				$connection->createUser($_POST['name'], $_POST['password'], $_POST['desc']);
				$exitpage='users';
				$smarty->assign('data',$connection->getUsers()->getAll());
			}else{
				$exitpage='createuser';
			}
			break;
		case 'edituser':
			if($_GET['do'] == 1) {
				$connection->editUser($_GET['name'], $_POST['password'], $_POST['desc']);
				$exitpage='users';
				$smarty->assign('data',$connection->getUsers()->getAll());
			}else{
				$exitpage='edituser';
				$smarty->assign('name',$_GET['name']);
				$smarty->assign('desc',$_GET['desc']);
			}
			break;
		case 'delgroup':
			$connection->removeGroup($_GET['name']);
			$smarty->assign('data',$connection->getGroups()->getAll());
			$exitpage='groups';
			break;
		case 'creategroup':
			if($_GET['do'] == 1) {
				$connection->createGroup($_POST['name'], $_POST['desc']);
				$exitpage='groups';
				$smarty->assign('data',$connection->getGroups()->getAll());
			}else{
				$exitpage='creategroup';
			}
			break;
		case 'addmember':
			if($_GET['do'] == 1) {
				$connection->addMember($_GET['group'], $_POST['name']);
				$exitpage='groups';
				$smarty->assign('data',$connection->getGroups()->getAll());
			}else{
				$exitpage='addmember';
				$smarty->assign('group',$_GET['group']);
				$smarty->assign('users',$connection->getUsers()->getAll());
			}
			break;
		case 'delmember':
			$connection->removeMember($_GET['group'], $_GET['name']);
			$smarty->assign('data',$connection->getGroups()->getAll());
			$exitpage='groups';
			break;
		case 'delbridge':
			$connection->removeBridge($_GET['src'],$_GET['srctype'],$_GET['dst'],$_GET['dsttype']);
			$smarty->assign('data',$connection->getBridges()->getAll());
			$exitpage='bridges';
			break;
		case 'createbridge':
			if($_GET['do'] == 1) {
				$connection->createBridge($_POST['src'],$_POST['srctype'],$_POST['dst'],$_POST['dsttype'],$_POST['selector']);
				$exitpage='bridges';
				$smarty->assign('data',$connection->getBridges()->getAll());
			}else{
				$exitpage='createbridge';
			}
			break;
		case 'committransaction':
			$connection->commitTransaction($_GET['name']);
			$smarty->assign('data',$connection->getTransactions()->getAll());
			$exitpage='transactions';
			break;
		case 'rollbacktransaction':
			$connection->rollbackTransaction($_GET['name']);
			$smarty->assign('data',$connection->getTransactions()->getAll());
			$exitpage='transactions';
			break;
		default:
			$exitpage = 'error';
			break;
	}
	$smarty->display($exitpage.'.tpl');
}
?>