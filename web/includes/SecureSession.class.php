<?php

class SecureSession
{
  var $check_browser = true;
  var $check_ip_blocks = 0;
  var $secure_word = 'be57ndr57KH4JDNFS7D978sdg3b467rfm89m8o9ozn78N=GZN=86gn907FN957fb';

  function Open()
  {
    $_SESSION['ss_fprint'] = $this->_Fingerprint();
  }

  function Check()
  {
    return (isset($_SESSION['ss_fprint'])
      && $_SESSION['ss_fprint'] == $this->_Fingerprint());
  }

	function UnregisterAll()
	{
		$_SESSION['uname']=null;
		unset($uname);
		$_SESSION['server']=null;
		unset($server);
		$_SESSION['passwd']=null;
		unset($passwd);
		$_SESSION['loggedin']=false;
		unset($loggedin);
	}

  function _Fingerprint()
  {
    $fingerprint = $this->secure_word;
    if ($this->check_browser)
    {
      $fingerprint .= $_SERVER['HTTP_USER_AGENT'];
    }
    if ($this->check_ip_blocks)
    {
      $num_blocks = abs(intval($this->check_ip_blocks));
      if ($num_blocks > 4)
      {
        $num_blocks = 4;
      }
      $blocks = explode('.', $_SERVER['REMOTE_ADDR']);
      for ($i=0; $i<$num_blocks; $i++)
      {
        $fingerprint .= $blocks[$i] . '.';
      }
    }
    return sha1($fingerprint);
  }
}
?>