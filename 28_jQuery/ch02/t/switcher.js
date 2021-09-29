
// 乱成一团的的代码，执行成什么结果不太清楚...
$(document).ready(function() {
    $('#switcher-default').addClass('selected');

    $('#switcher').click(function(event) {
        if ($(event.target).is('button')) {
            var bodyClass = event.target.id.split('-')[1];
            $('body').removeClass().addClass(bodyClass);
            $('#switcher button').removeClass('selected');
            $(event.target).addClass('selected');
            event.stopPropagation();
        }
    });

    var toggleSwitcher = function(event) {
        if (! $(event.target).is('button')) {
            $('#switcher button').toggleClass('hidden');
        }
    };
    $('#switcher').on('click', toggleSwitcher);

    $('#switcher button').click(function() {
        $('#switcher').off('click', toggleSwitcher);
        if (this.id == 'switcher-default') {
            $('#switcher').on('click', toggleSwitcher);
        }
    });

    $('#switcher-default').click(function() {
        $('#switcher').on('click.collapse', toggleSwitcher);
    });

    $('#switcher h3').hover(function() {
        $(this).addClass('hover');
    }, function() {
        $(this).removeClass('hover');
    });

});
