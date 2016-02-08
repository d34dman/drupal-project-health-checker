<header class="main-header">
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>
  <!-- Logo -->
  <a href="/" class="logo">
    <!-- mini logo for sidebar mini 50x50 pixels -->
    <span class="logo-mini"><b>D</b>P</span>
    <!-- logo for regular state and mobile devices -->
    <span class="logo-lg"><b>Drupal</b> project health</span>
  </a>
  <!-- Header Navbar: style can be found in header.less -->
  <nav class="navbar navbar-static-top" role="navigation">
    <!-- Sidebar toggle button-->
    <a href="#" class="sidebar-toggle" data-toggle="offcanvas" role="button">
      <span class="sr-only">Toggle navigation</span>
      <span class="icon-bar"></span>
      <span class="icon-bar"></span>
      <span class="icon-bar"></span>
    </a>
    <div class="navbar-custom-menu">
      <ul class="nav navbar-nav">
        <?php if ($profile['uid']): ?>
          <!-- User Account: style can be found in dropdown.less -->
          <li class="dropdown user user-menu">
            <a href="#" class="dropdown-toggle clearfix" data-toggle="dropdown">
              <img src="<?php echo $profile['picture']; ?>" class="user-image" alt="User Image">
              <span class="hidden-xs user-name pull-left"><?php echo render($profile['name']); ?></span>
            </a>
            <ul class="dropdown-menu">
              <!-- User image -->
              <li class="user-header">
                <img src="<?php echo $profile['picture']; ?>" class="img-circle" alt="User Image">
                <p>
                  <?php echo render($profile['name']); ?>
                  <small><?php echo render($profile['member_since']); ?></small>
                </p>
              </li>
              <!-- Menu Body -->
              <li class="user-body">
                <div class="col-xs-4 text-center">
                  <a href="#">...</a>
                </div>
                <div class="col-xs-4 text-center">
                  <a href="#">...</a>
                </div>
                <div class="col-xs-4 text-center">
                  <a href="#">...</a>
                </div>
              </li>
              <!-- Menu Footer-->
              <li class="user-footer">
                <div class="pull-left">
                  <a href="/user" class="btn btn-default btn-flat">Profile</a>
                </div>
                <div class="pull-right">
                  <a href="/user/logout" class="btn btn-default btn-flat">Sign out</a>
                </div>
              </li>
            </ul>
          </li>
        <?php else: ?>

        <?php endif ?>
      </ul>
    </div>
  </nav>
</header>

<!-- =============================================== -->

<!-- Left side column. contains the sidebar -->
<aside class="main-sidebar">
  <!-- sidebar: style can be found in sidebar.less -->
  <section class="sidebar">
    <!-- Sidebar user panel -->
    <div class="user-panel">
      <div class="pull-left image">
        <img src="<?php echo $profile['picture']; ?>" class="img-circle" alt="User Image">
      </div>
      <div class="pull-left info">
        <p><?php echo render($profile['name']); ?></p>
        <a href="#"><i class="fa fa-circle text-success"></i> Online</a>
      </div>
    </div>
    <!-- search form -->
    <?php echo drupal_render($search_sidebar); ?>
    <!-- /.search form -->
    <!-- sidebar menu: : style can be found in sidebar.less -->
    <ul class="sidebar-menu">
      <li class="header">MAIN NAVIGATION</li>
      <li><a href="/projecthealth/view"><i class="fa fa-flask"></i> <span>Projects</span></a></li>
      <li><a href="/projecthealth/add"><i class="fa fa-plus"></i> <span>Add Snapshot</span></a></li>
    </ul>
  </section>
  <!-- /.sidebar -->
</aside>
