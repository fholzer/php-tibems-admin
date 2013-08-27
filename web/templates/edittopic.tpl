{ajax_form id='edittopic' method='post' url='index.php?type=edittopic&amp;f=getSubContent&amp;do=1' callback='form_submit'}
<table>
    <tr>
        <td>Topic Name:</td>
        <td><input type="hidden" name="name" value="{$data->getDn()}"/>{$data->getDn()}</td>
    </tr>
    <tr>
        <td>Prefetch:</td>
        <td><input type="text" name="prefetch" value="{$data->getPf()}" size="5"/>msgs (-1 = none)</td>
    </tr>
    <tr>
        <td>Overflow Policy:</td>
        <td><select name="overflow"><option value="0">default</option><option value="1"{if $data->getOp() == 1} selected="selected"{/if}>discard Old</option><option value="2"{if $data->getOp() == 2} selected="selected"{/if}>reject Incoming</option></select></td>
    </tr>
    <tr>
        <td>Max Bytes:</td>
        <td><input type="text" name="maxbytes" value="{$data->getMb()}" size="10"/>bytes</td>
    </tr>
    <tr>
        <td>Max Messages:</td>
        <td><input type="text" name="maxmsgs" value="{$data->getMm()}" size="10"/>msgs</td>
    </tr>
    <tr>
        <td>Msg Expiration:</td>
        <td><input type="text" name="expiration" value="{$data->getExpy()}" size="10"/>seconds</td>
    </tr>
    <tr>
        <td>Flowcontrol:</td>
        <td><input type="text" name="flowcontrol" value="{$data->getFcs()}" size="10"/>bytes</td>
    </tr>
    <tr>
        <td>Failsafe:</td>
        <td><input type="checkbox" name="failsafe"{if $data->isFailsafe() > 0} checked="checked"{/if}/></td>
    </tr>
    <tr>
        <td>Secure:</td>
        <td><input type="checkbox" name="secure"{if $data->isSecure() > 0} checked="checked"{/if}/></td>
    </tr>
    <tr>
        <td>Global:</td>
        <td><input type="checkbox" name="isglobal"{if $data->isGlobal() > 0} checked="checked"{/if}/></td>
    </tr>
    <tr>
        <td>Senders Name:</td>
        <td><input type="checkbox" name="sname"{if $data->senderName() > 0} checked="checked"{/if}/></td>
    </tr>
    <tr>
        <td>Senders Name Enforced:</td>
        <td><input type="checkbox" name="snameenf"{if $data->senderNameEnforced() > 0} checked="checked"{/if}/></td>
    </tr>
    <tr>
        <td colspan="2" align="center"><input type="submit" value="update"/></td>
    </tr>
</table>
{/ajax_form}
