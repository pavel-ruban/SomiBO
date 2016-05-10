<div id="somi-door-utils">
  <a href="/" id="somi-open-door">Open Door</a>
  <form method="post" action="/">
    <label for="track-rfids" class="tracker" >Track last rfid tag?</label>
    <input id="track-rfids" type="checkbox" name="track_rfids" />
    <span id="rfid-tracker"><?php echo !empty($_POST['track_rfid_status']) ? file_get_contents('tracker.txt') : ''; ?></span>
  </form>
</div>