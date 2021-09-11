function nextChapter()
    clear_options()
    add_text("Jeff Bezos", "moving on!", 255, 0, 0)
    add_option("No, don't!");
    jump_end()
    coroutine.yield()
    
    while true do
        add_text("Jeff Bezos", "Yes! Moving on!", 255, 0, 0)
        clear_options()
        add_option("Okay...")
        add_option("No! No moving on!")
        jump_end()
        coroutine.yield()
        if result == 1 then
            close_dialogue(false)
            break
        end
    end
end

function start()
    
    add_text("Jeff Bezos", 'Jeff looks up at you; "Hello there! How can I help you?" he says, looking at you questioningly.', 255, 0, 0)

    add_option("Hello, I am interested in purchasing an amazon prime subscription")
    add_option("I am here to complain about amazons poor working conditions and encourage you to allow your workers to unionize")
    add_option("I love you Jeff Bezos, I've loved you for years!")
    
    jump_end()
    coroutine.yield()
    
    clear_options()
    
    if result == 1 then
        add_text("Jeff Bezos", "Please go to amazon.com/prime, I do not handle individual subscriptions...", 255, 0, 0)
        add_option('Okay, thank you.')
        jump_end()
        coroutine.yield()
        nextChapter()
    elseif result == 2 then
        add_text('Jeff Bezos', 'I will think about it.', 255, 0, 0)
        add_option('Please do.')
    else
        add_text('Jeff Bezos', 'I love you too! Lets get married!', 255, 0, 0)
        add_option('TO OUR WEDDING!')
    end
end