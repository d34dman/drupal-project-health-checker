<section class="content">
  <div class="row">
    <div class="col-md-12 col-sm-12 col-xs-12">
      <div class="info-box bg-orange">
        <span class="info-box-icon"><i class="fa fa-info"></i></span>
        <div class="info-box-content">
          <span class="info-box-text">Index status</span>
          <span class="info-box-number"><?php echo $snapshot->progress; ?>%</span>
          <div class="progress">
            <div class="progress-bar" style="width: <?php echo $snapshot->progress; ?>%"></div>
          </div>
          <span class="progress-description">
            <?php echo format_date($snapshot->created); ?>
          </span>
        </div>
      </div>
    </div>
  </div>

  <div class="row">
    <div class="col-lg-12 col-xs-12">
      <!-- small box -->
      <div class="small-box bg-gray">
        <div class="inner">
          <h3 class="title"></h3>
          <p class="message-default">
            Snapshot have been queued for creation. The data for snapshot is retrived from Drupal.org
            using its REST API on cron runs. If there is a huge number of user activity on the project then the
            snapshot creation might take days (for example Drupal Core project takes about 3 days to complete).
            <br/>
          </p>
          <p class="message-dynamic">
          </p>
        </div>
        <div class="icon">
          <i class="fa fa-info"></i>
        </div>
        <a href="/" class="small-box-footer">
          <i class="fa fa-home"></i> Home
        </a>
      </div>
    </div>
    <!-- ./col -->
  </div>
</section>
