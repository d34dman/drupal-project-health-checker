<!-- Main content -->
<section class="content">
  <a id="main-content"></a>
  <div class="region region-content">
    <section id="projecthealth-snapshot" class="block block-system clearfix" data-json-url="<?php echo $json_url; ?>">
      <section class="content">
        <div class="row">
          <div class="col-md-3 col-sm-6 col-xs-12">
            <div class="info-box js-snapshot">
              <span class="info-box-icon"><i class="fa fa-info"></i></span>
              <div class="info-box-content">
                <span class="info-box-text">Index status</span>
                <span class="info-box-number">0%</span>
                <div class="progress">
                  <div class="progress-bar"></div>
                </div>
                <span class="progress-description">
                Unknown</span>
              </div>
            </div>
          </div>
          <div class="col-md-3 col-sm-6 col-xs-12">
            <div class="info-box js-project-issues">
              <span class="info-box-icon"><i class="fa fa-star-o"></i></span>
              <div class="info-box-content">
                <span class="info-box-text">Issues</span>
                <span class="info-box-number"></span>
                <div class="progress">
                  <div class="progress-bar"></div>
                </div>
                <span class="progress-description">
                </span>
              </div>
            </div>
          </div>
          <div class="col-md-2 col-sm-6 col-xs-12">
            <div class="info-box js-project-download">
              <span class="info-box-icon "><i class="fa fa-download"></i></span>
              <div class="info-box-content">
                <span class="info-box-text">Downloads</span>
                <span class="info-box-number"></span>
              </div>
              <!-- /.info-box-content -->
            </div>
          </div>
          <div class="col-md-2 col-sm-6 col-xs-12">
            <div class="info-box js-project-comments">
              <span class="info-box-icon"><i class="fa fa-comments-o"></i></span>
              <div class="info-box-content">
                <span class="info-box-text">Comments</span>
                <span class="info-box-number"></span>
                <div class="progress hidden">
                  <div class="progress-bar"></div>
                </div>
                <span class="progress-description">
                </span>
              </div>
            </div>
          </div>
          <div class="col-md-2 col-sm-6 col-xs-12">
            <div class="info-box js-project-open-issues">
              <span class="info-box-icon"><i class="fa fa-exclamation"></i></span>
              <div class="info-box-content">
                <span class="info-box-text">Open Issues</span>
                <span class="info-box-number count"></span>
                <div class="progress hidden">
                  <div class="progress-bar"></div>
                </div>
                <span class="progress-description">
                </span>
                <a href="#" target="_blank" class="issues-link hidden">
                  <i class="fa fa-arrow-circle-right"></i>
                </a>
              </div>
            </div>
          </div>
        </div>
        <div class="row">
          <div class="col-md-6 col-sm-6 col-xs-12">
            <div class="box box-solid viz-box">
              <div class="box-header ui-sortable-handle">
                <i class="fa fa-map-marker"></i><h3 class="box-title">Activity Map</h3>
              </div>
              <div class="box-body">
                <div id="map-container" style="width: 100%; height: 300px;">
                </div>
              </div>
              <div class="box-footer no-border">
                <ul id="map-container-control" class="nav nav-pills nav-justified">
                  <li role="presentation"><a href="#" data-trigger="total">Total<br/><small>Issues + Comments</small></a></li>
                  <li role="presentation"><a href="#" data-trigger="issues">Issues<br/><small>&nbsp;</small></a></li>
                  <li role="presentation"><a href="#" data-trigger="comments">Comments<br/><small>&nbsp;</small></a></li>
                  <li role="presentation"><a href="#" data-trigger="users">Users<br/><small>&nbsp;</small></a></li>
                </ul>
              </div>
            </div>
          </div>
          <div class="col-md-6 col-sm-6 col-xs-12">
            <div class="box box-solid viz-box">
              <div class="box-header ui-sortable-handle">
                <i class="fa fa-users"></i><h3 class="box-title">User Demographics</h3>
              </div>
              <div class="box-body">
                <div id="user-container" style="width: 100%; height: 300px;">
                </div>
              </div>
              <div class="box-footer no-border">
                <ul id="user-container-control" class="nav nav-pills nav-justified">
                  <li role="presentation"><a href="#" data-trigger="age">Age<br/><small>Years since user joined Drupal.org</small></a></li>
                  <li role="presentation"><a href="#" data-trigger="last-activity">Last Active Time<br/><small>Year when the user last participated in issues/comment.</small></a></li>
                </ul>
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
                  Activity of users who have not disclosed their location are not included.
                  <br/>
                  Arbitary threshold have been used to colour the info cards as of now.
                  <br/>
                </p>
                <p class="message-dynamic">
                </p>
              </div>
              <div class="icon">
                <i class="fa fa-info"></i>
              </div>
              <a href="http://d34dman.github.io/dcasia16-drupal-visualization/" class="small-box-footer">
                <i class="fa fa-home"></i> Home
              </a>
            </div>
          </div>
          <!-- ./col -->
        </div>
      </section>
    </section> <!-- /.block -->
  </div>
</section><!-- /.content -->
<script src="//cdnjs.cloudflare.com/ajax/libs/d3/3.5.3/d3.min.js"></script>
<script src="//d3js.org/queue.v1.min.js"></script>
<script src="//cdnjs.cloudflare.com/ajax/libs/topojson/1.6.9/topojson.min.js"></script>
<script src="/sites/all/modules/development/projecthealth/js/datamaps.world.min.js"></script>
<script src="/sites/all/modules/development/projecthealth/js/d3.hexbin.min.js"></script>
<script src="/sites/all/modules/development/projecthealth/js/hexbin.js"></script>
<script src="/sites/all/modules/development/projecthealth/js/script.js"></script>
