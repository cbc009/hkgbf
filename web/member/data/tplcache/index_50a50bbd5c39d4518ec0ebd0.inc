<?php
if(!isset($GLOBALS['_vars'])) $GLOBALS['_vars'] = array(); 
$fields = array();
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>会员中心 -<?php echo $cfg_webname; ?></title>
<meta http-equiv="Content-Type" content="text/html; charset=<?php echo $cfg_soft_lang; ?>" />
<link href="templets/style/index.css" rel="stylesheet" type="text/css" />
<link href="templets/style/boxy.css" rel="stylesheet" type="text/css" />
<script type="text/javascript" src="templets/js/j.js"></script>
<script type="text/javascript" src="templets/js/jquery.boxy.js"></script>
<script type="text/javascript" src="templets/js/load_index.js"></script>
<script type="text/javascript" src="templets/js/leftmenu.js"></script>
<script type="text/javascript" src="templets/js/face.js"></script>
<script type="text/javascript" src="templets/js/Dialog.js"></script>
<script type="text/javascript" src="templets/js/jquery.js"></script>
<script type="text/javascript" src="templets/js/feed.js"></script>
<script language='javascript'>
	function msgSubmit(form) {
		//var id=form.id.value;
		var content = form.share_textarea.value;
		if( content == '来,说点啥吧...' ) content = '';
		if ( content == '' ) {
			alert('请输入内容'); return false;
		}
		$.ajax({
			type:'POST',
			url:'index_do.php?fmdo=moodmsg&dopost=sendmsg',
			cache:false,
			data:'&content='+encodeURIComponent(content),
			dataType:'json',
			success:function(message){
				if ( message.type == 'success' ) {
					$('#share_textarea').val('');
					$('#moodcontent').html(message.data);
				} else {
					alert(message.data);
				}
			}
		});
	}
</script>
</head>
<body>
<div id="baseParent">
    <div id="mood_face_bg"></div>
	<div id="mood_msg_menu" class="faceBox" style="position: absolute; top: 332px;display: none;">
        <ul>
        <?php
        for($i=1;$i<=64;$i++)
        {
         ?>        
            <li><img style="cursor: pointer; position: relative;" src="templets/images/smiley/<?php echo $i ?>.gif" id="face1" onclick="addFace(<?php echo $i ?>)"/></li>
         <?php
         }
         ?>
        </ul>
	</div>

</div>
<div id="main">
<?php include(DEDEMEMBER."/templets/head.htm"); ?>
<div id="content" class="w960 clearfix">
  <?php include(DEDEMEMBER."/templets/menu.php"); ?>
  <div class="755">
    <div class="main-wrap">
      <dl class="sns-avatar">
        <dt>
          <div class="s120"> <a href="<?php echo $cfg_cmsurl;?>/member/index.php?uid=<?php echo $cfg_ml->M_LoginID; ?>"><img src="<?php echo $cfg_ml->fields['face']; ?>" width="100" height="100" alt="您的形象"/></a> </div>
        </dt>
        <dd class="av-index">
          <ul>
            <li class="name"><?php echo $cfg_ml->M_LoginID; ?><span><?php echo $cfg_ml->M_MbType; ?>用户</span></li>
            <?php
             if(is_array($moodmsg)){
            ?>
            <li class="other" id="moodcontent"><?php echo $moodmsg['msg'];?></li>
            <?php
              } else {
            ?>
             <li class="other" id="moodcontent">还没有个性签名，试试在下面输入框中填写</li>
             <?php
             }
             ?>
            <li class="sign"><?php echo $cfg_ml->GetSta($dsql); ?></li>
          </ul>
          <div class="msg">
            <p>短消息: <em> <a href="pm.php?TB_iframe=true&height=600&width=700" title="我的短信息" target="_blank"> <?php echo $pms['nums'];?></a> </em> 评论: <em> <a href="caicai.php" title="发出的评论"><?php echo $minfos['feedback']; ?></a> </em> 收藏: <em> <a href="mystow.php" title="收藏夹"><?php echo $minfos['stow']; ?></a> </em> 其它: <em><a href="javascript:;"><?php echo $minfos['archives']; ?></a> </em> 文章:<em> <a href="content_list.php?channelid=1" title="已发布的文章"><?php echo $minfos['article']; ?></a> </em>图集: <em> <a href="content_list.php?channelid=2" title="管理图集"><?php echo $minfos['album']; ?></a> </em> 软件: <em> <a href="content_list.php?channelid=3" title="已发布的软件"><?php echo $minfos['soft']; ?></a> </em> 商品:</a> <em> <a href="shops_products.php" title="购买的商品"><?php echo $minfos['shop']; ?></a> </em> </p>
          </div>
        </dd>
      </dl>
      <div class="share">
        <div class="share01"> </div>
        <div class="share02">
          <form target="hidden_frame" method="post" enctype="multipart/form-data" name="msgmood" action="#">
            <input id="share_textarea" type="text" value="来,说点啥吧..." onclick="showFace()"/>
            <button id="btn_submit" type="button" onclick="msgSubmit(this.form)">发表</button>
          </form>
        </div>
      </div>
      <div id="sns-feeds">
          <div class="indexTab">
            <ul>
              <li id="arcticle"><a href="javascript:void(0)">最新文档</a></li>
              <li class="thisTab" id="myfeed"><a href="javascript:void(0)">我的动态</a></li>
              <li id="allfeed"><a href="javascript:void(0)">全站动态</a></li>
            </ul>
          </div>
        <div class="sns-box" id="FeedText"></div>
      </div>
    </div>
    <div class="col-extra">
      <div class="sns-box">
        <div class="hd">
          <h3>信息统计</h3>
        </div>
        <div class="sns-avatar-m">
          <dl class="statistics">
            <dt>空间访问量：</dt>
            <dd><?php echo $minfos['homecount']; ?></dd>
            <dt>文档总点击：</dt>
            <dd><?php echo $minfos['pagecount']; ?></dd>
            <dt>好友数量：</dt>
            <dd><?php echo $minfos['friend']; ?></dd>
            <dt>空间版本：</dt>
            <dd><?php
       			if($cfg_mb_lit=='Y') echo '精简版';
        		else echo '完全版';
        	?></dd>
            <dt>上传限制：</dt>
            <dd><?php echo $cfg_mb_upload_size; ?> KB</dd>
            <dt>空间大小：</dt>
            <dd><?php echo $minfos['totaluse']."/".$cfg_mb_max; ?> MB</dd>
          </dl>
        </div>
      </div>
      <div class="sns-box">
        <div class="hd">
          <h3>欢迎新朋友</h3>
        </div>
        <div class="sns-avatar-m">
          <ul>
            <?php
				foreach ($newfriends as $newfriend)
				{
			 ?>
            <li class="pic"><a target="_blank" href="<?php echo $cfg_cmsurl;?>/member/index.php?uid=<?php echo $newfriend['userid'];?>">
            <?php
            if(!$newfriend['face']==""){
             echo "<img src=".$newfriend['face']." width='48' height='48' />";
            }else{
             if($newfriend['sex']=='女') echo "<img src='templets/images/dfgirl.png' width='48' height='48' />";
             else echo "<img src='templets/images/dfboy.png' width='48' height='48' />";
            }
            ?>
            </a><span class="name"><a target="_blank" href="<?php echo $cfg_cmsurl;?>/member/index.php?uid=<?php echo $newfriend['userid'];?>"><?php echo $newfriend['uname'];?></a></span></li>
             <?php
                }
              ?>
          </ul>
        </div>
      </div>
      <div class="clr"></div>
      <div class="sns-box">
        <div class="hd">
          <h3>我的好友</h3>
        </div>
        <div class="sns-avatar-m">
          <ul>
             <?php
				foreach ($friends as $friend)
				{
			 ?>
            <li class="pic"><a target="_blank" href="<?php echo $cfg_cmsurl;?>/member/index.php?uid=<?php echo $friend['floginid'];?>">
            <?php
            if(!$friend['face']==""){
             echo "<img src=".$friend['face']." width='48' height='48' />";
            }else{
             if($friend['sex']=='女') echo "<img src='templets/images/dfgirl.png' width='48' height='48' />";
             else echo "<img src='templets/images/dfboy.png' width='48' height='48' />";
            }
            ?>
            </a><span class="name"><a target="_blank" href="<?php echo $cfg_cmsurl;?>/member/index.php?uid=<?php echo $friend['floginid'];?>"><?php echo $friend['funame'];?></a></span></li>
             <?php
                }
              ?>
          </ul>
        </div>
      </div>
      <div class="sns-box">
        <div class="bd ">
          <form action="search.php">
            <p style="margin-bottom:9px">搜索用户</p>
            <input class="text1" style="width:130px;" type="text" value="" name="keyword"/>
            <button class="button1" type="submit">找人</button>
          </form>
        </div>
      </div>
    </div>
  </div>
</div>
<?php include(DEDEMEMBER."/templets/foot.htm"); ?>
</div>
</body>
</html>