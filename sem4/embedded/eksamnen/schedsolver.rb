#!/usr/bin/env ruby

require 'optparse'

class Scheduler
  def initialize()
    @states = []
    @tasks = []
  end

  def loadtasks(tasks)
    @tasks = tasks
  end


  def printHeader()
    print "i".ljust(4, ' ')
    @tasks.length.times do |i|
      print "T#{i.to_s()}".ljust(4, ' ')
    end
    @tasks.length.times do |i|
      print "R#{i.to_s()}".ljust(4, ' ')
    end
    @tasks.length.times do |i|
      print "D#{i.to_s()}".ljust(4, ' ')
    end
    puts
  end

  def printState(index, state)
    print (index).to_s().ljust(4, ' ')
    @tasks.length.times do |i|
      print state[:task] == i ? "|" : " "
      print " "*3
    end

    state[:remain].each_with_index do |r, i|
      print r.to_s().ljust(4, ' ')

    end

    @tasks.each do |task|
      deadline = task[:deadline] - (index % task[:period])
      print deadline.to_s().ljust(4, ' ')
    end

    puts
  end

  def nextTask(index)
    choices = []

    if @states.length.zero?
      choices = @tasks.length.times.to_a
    else
      @states.last[:remain].each_with_index do |r, i|
        choices << i if r > 0
      end
    end

    if choices.length.zero?
      return nil
    elsif choices.length == 1
      # If there is only one choice return that
      return choices[0]
    end


    loop do
      print "Next #{choices.to_s}:"
      input = gets
      if input == "\n" and @states.last
        return @states.last[:task]
      end
      choice = Integer(input)
      if choices.include?(choice)
        return choice
      end
    end
  end

  def calcNextState(index)
    curtask = nil
    # We should not run at the begining
    if index > 0
      curtask = nextTask(index)
    end
    new = {:task => curtask, :remain => []}
    @tasks.each_with_index do |task, i|
      # Check for deadline miss
      intoperiod = index % task[:period]
      if intoperiod >= task[:deadline] && @states.last[:remain][i] > 0
        puts "Deadline missed in task #{i}"
        exit
      end
      # Check if start of new period
      if index % task[:period] == 0
        new[:remain] << task[:complete]
      else
        new[:remain] << @states.last[:remain][i]
      end
    end

    # Decrease the selected task
    if curtask
      new[:remain][curtask] -= 1 unless new[:remain][curtask].zero?
    end

    return new
  end

  def runtiltask(task)
    printHeader()
    (0..).step do |i|
      new = calcNextState(i)
      @states << new

      printState(i, new)

      if new[:remain][task] == 0
        break
      end
    end
  end

  def run(runtil = nil)
    if !runtil
      # Run LCM times
      runtil = @tasks[0][:period]
      @tasks.drop(1).each do |task|
        runtil = task[:period].lcm(runtil)
      end
    end

    runtil.times do |i|
      new = calcNextState(i)
      @states << new

      printState(i, new)
    end
  end
end

def taskFromString(str)
  fields = str.split(",")
  if fields.length < 2
    raise "#{str} does not contain enough fields"
  end

  # Run for each field
  def parseField(f, default = 0)
    return f == nil ? Integer(default) : Integer(f)
  end

  task = {
    :period => parseField(fields[0]),
    :complete => parseField(fields[1]),
    :deadline => parseField(fields[2], fields[0])
  }

  return task
end

class FixedSched < Scheduler
  alias_method :parent_init, :initialize
  def initialize(priorities)
    @priorities = priorities

    parent_init
  end

  def nextTask(index)
    @priorities.each do |taskid|
      if !@states.last or @states.last[:remain][taskid] > 0
        return taskid
      end
    end

    return nil
  end
end

class RmaSched < Scheduler
  def nextTask(index)
    smallestTask = nil

    @tasks.each_with_index do |task, i|
      if @states.last and @states.last[:remain][i] == 0
        next
      end

      smallestTask = i if !smallestTask or task[:period] < @tasks[i][:period]
    end

    return smallestTask
  end
end

class EdfSched < Scheduler
  def nextTask(index)
    smallestTask = nil
    closestDead = nil

    @tasks.each_with_index do |task, i|
      if @states.last and @states.last[:remain][i] == 0
        next
      end

      deadline = task[:deadline] - (index % task[:period])

      if !smallestTask or deadline < closestDead
        smallestTask = i
        closestDead = deadline
      end
    end

    return smallestTask
  end
end

options = {}
OptionParser.new do |opts|
  opts.on("-f", "--taskfile FILE", "Load tasks from FILE") do |f|
    options[:taskfile] = f
  end
  opts.on("--until-done TASK", "Run until TASK finishes") do |task|
    options[:runtiltask] = Integer(task)
  end
  opts.on("--until TIME", "Run til specified time") do |time|
    options[:runtil] = Integer(time)
  end
  opts.on("--sched-rma", "Schedule using rma") do
    options[:sched] = RmaSched.new()
  end
  opts.on("--sched-edf", "Schedule using edf") do
    options[:sched] = EdfSched.new()
  end
  opts.on("--sched-fixed PRIO", "Schedule using fixed priority list PRIO") do |prio|
    prio = prio.split(",")
    prio.map! {|p| Integer(p) }
    options[:sched] = FixedSched.new(prio)
  end
end.parse!

tasks = []

if options[:taskfile]
  File.readlines(options[:taskfile]).each do |line|
    tasks << taskFromString(line)
  end
else
  puts "T  : period,completion time[,deadline]"

  loop do
    print "T#{ tasks.length }: "
    input = gets
    if !input or input.delete_suffix!("\n") == ""
      break
    end

    tasks << taskFromString(input)
  end
end

puts tasks.inspect

sch = nil
if options[:sched]
  sch = options[:sched]
else
  sch = Scheduler.new()
end
sch.loadtasks(tasks)

if options[:runtiltask]
  sch.runtiltask(options[:runtiltask])
else
  sch.run(options[:runtil])
end
